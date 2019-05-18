// 
// tsh - A tiny shell program with job control
// 
// <Put your name and login ID here> Mohammed Hejazi/mohe2088 
//

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string>

#include "globals.h"
#include "jobs.h"
#include "helper-routines.h"

//
// Needed global variable definitions
//

static char prompt[] = "tsh> ";
int verbose = 0;

//
// You need to implement the functions eval, builtin_cmd, do_bgfg,
// waitfg, sigchld_handler, sigstp_handler, sigint_handler
//
// The code below provides the "prototypes" for those functions
// so that earlier code can refer to them. You need to fill in the
// function bodies below.
// 

void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

//
// main - The shell's main routine 
//
int main(int argc, char **argv) 
{
  int emit_prompt = 1; // emit prompt (default)

  //
  // Redirect stderr to stdout (so that driver will get all output
  // on the pipe connected to stdout)
  //
  dup2(1, 2);

  /* Parse the command line */
  char c;
  while ((c = getopt(argc, argv, "hvp")) != EOF) {
    switch (c) {
    case 'h':             // print help message
      usage();
      break;
    case 'v':             // emit additional diagnostic info
      verbose = 1;
      break;
    case 'p':             // don't print a prompt
      emit_prompt = 0;  // handy for automatic testing
      break;
    default:
      usage();
    }
  }

  //
  // Install the signal handlers
  //

  //
  // These are the ones you will need to implement
  //
  Signal(SIGINT,  sigint_handler);   // ctrl-c
  Signal(SIGTSTP, sigtstp_handler);  // ctrl-z
  Signal(SIGCHLD, sigchld_handler);  // Terminated or stopped child

  //
  // This one provides a clean way to kill the shell
  //
  Signal(SIGQUIT, sigquit_handler); 

  //
  // Initialize the job list
  //
  initjobs(jobs);

  //
  // Execute the shell's read/eval loop
  //
  for(;;) {
    //
    // Read command line
    //
    if (emit_prompt) {
      printf("%s", prompt);
      fflush(stdout);
    }

    char cmdline[MAXLINE];

    if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
      app_error("fgets error");
    }
    //
    // End of file? (did user type ctrl-d?)
    //
    if (feof(stdin)) {
      fflush(stdout);
      exit(0);
    }

    //
    // Evaluate command line
    //
    eval(cmdline);
    fflush(stdout);
    fflush(stdout);
  } 

  exit(0); //control never reaches here
}
  
/////////////////////////////////////////////////////////////////////////////
//
// eval - Evaluate the command line that the user has just typed in
// 
// If the user has requested a built-in command (quit, jobs, bg or fg)
// then execute it immediately. Otherwise, fork a child process and
// run the job in the context of the child. If the job is running in
// the foreground, wait for it to terminate and then return.  Note:
// each child process must have a unique process group ID so that our
// background children don't receive SIGINT (SIGTSTP) from the kernel
// when we type ctrl-c (ctrl-z) at the keyboard.
//
void eval(char *cmdline) 
{
    pid_t process; // sets process id type to variable process 
  /* Parse command line */
  //
  // The 'argv' vector is filled in by the parseline
  // routine below. It provides the arguments needed
  // for the execve() routine, which you'll need to
  // use below to launch a process.
  //
  char *argv[MAXARGS];

  //
  // The 'bg' variable is TRUE if the job should run
  // in background mode or FALSE if it should run in FG
  //
  int bg = parseline(cmdline, argv);   // 
  if (argv[0] == NULL)  
    return;   /* ignore empty lines */
  if(builtin_cmd(argv) == 0)
  {
      if((process = fork())== 0) // check if pid is a child
      {
          if(execve(argv[0],argv,environ) == -1) // 3 parameters, filename, argument, environment, -1 means failed
          {
              printf("%s: command not found \n",argv[0]);
              exit(0);
          }
      }else //parent
      {
          int jid = pid2jid(process); // from process id, find job id       pid2jid wont work for child process, bc its looking for id atleast 1 or bigger
          if(bg)
          {
              addjob(jobs,process,BG,cmdline); //add job searches until it finds an empty slot so it can add it to jobs array
              printf("[%i] (%i) %c\n", jid, process, *cmdline );
          }else{ // fg
              addjob(jobs, process, FG, cmdline);
              waitfg(process); // wait is to avoid zombie shits
              
          }
      }
  }

  return;
}


/////////////////////////////////////////////////////////////////////////////
//
// builtin_cmd - If the user has typed a built-in command then execute
// it immediately. The command name would be in argv[0] and
// is a C string. We've cast this to a C++ string type to simplify
// string comparisons; however, the do_bgfg routine will need 
// to use the argv array as well to look for a job number.
//
int builtin_cmd(char **argv) 
{
  string cmd(argv[0]);
  if(cmd == "quit")
  {
      exit(0);
  }
  else if(cmd == "fg")
    {
        do_bgfg(argv);
        return 1;
    }
  else if(cmd == "bg")
  {
      do_bgfg(argv);
      return 1;
  }
  else if(cmd == "jobs")
  {
      listjobs(jobs);
      return 1;
  }
      
  return 0;     /* not a builtin command */
}

/////////////////////////////////////////////////////////////////////////////
//
// do_bgfg - Execute the builtin bg and fg commands
//
void do_bgfg(char **argv) 
{
  struct job_t *jobp=NULL;
    
  /* Ignore command if no argument */
  if (argv[1] == NULL) {
    printf("%s command requires PID or %%jobid argument\n", argv[0]);
    return;
  }
    
  /* Parse the required PID or %JID arg */
  if (isdigit(argv[1][0])) {
    pid_t pid = atoi(argv[1]); // character to int
    if (!(jobp = getjobpid(jobs, pid))) {       //getjobpid returns adress,,,, checks job with matching pid
      printf("(%d): No such process\n", pid);
      return;
    }
  }
  else if (argv[1][0] == '%') {    // % = job id
    int jid = atoi(&argv[1][1]);
    if (!(jobp = getjobjid(jobs, jid))) {   // searches job until it finds job with matching id, returns address of indeci
      printf("%s: No such job\n", argv[1]);  // doesnt actually run if its true
      return;
    }
  }	    
  else {
    printf("%s: argument must be a PID or %%jobid\n", argv[0]); // invalid input
    return;
  }

  //
  // You need to complete rest. At this point,
  // the variable 'jobp' is the job pointer
  // for the job ID specified as an argument.
  //
  // Your actions will depend on the specified command
  // so we've converted argv[0] to a string (cmd) for
  // your benefit.
  //
  string cmd(argv[0]);
    if(cmd == "fg")
    {
        jobp->state = FG;     // Going to jobp and setting its state to FG
        kill(-jobp->pid,SIGCONT);  // kills process ID, count tells proccess to pickup where left off
        waitfg(jobp->pid);  //wait because its fg
    }
    else{
        jobp->state = BG; //change state to bg
        printf("[%d] (%d) %s \n", jobp->jid, jobp->pid, jobp->cmdline); //print info
        kill(-jobp->pid,SIGCONT);
    }

  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// waitfg - Block until process pid is no longer the foreground process
//
void waitfg(pid_t pid)
{
    while(true)
    {
        bool found = false;
        for(int i = 0; i < MAXJOBS; i++)  //for loop is going through all of jobs to find a matching pid
        {
            if(jobs[i].pid == pid)
            {
                found = true;
                if(jobs[i].state == FG)
                {
                    sleep(10);
                }else{
                    return;   // pid is in the jobs array
                }
            }
        }
        if(found==false) //pid not in the jobs array
        {
            return;
        }
    }

  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// Signal handlers
//


/////////////////////////////////////////////////////////////////////////////
//
// sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
//     a child job terminates (becomes a zombie), or stops because it
//     received a SIGSTOP or SIGTSTP signal. The handler reaps all
//     available zombie children, but doesn't wait for any other
//     currently running children to terminate.  
//
void sigchld_handler(int sig) 
{
  pid_t process; //WNOHANG returns 0 for child process. suspends process until child terminates
  int kos; //integer for status
  while((process = waitpid(-1, &kos, WNOHANG | WUNTRACED)) > 0) {    // Reap a zombie child
        int jid = pid2jid(process); //WUNTRACED suspend calling process until waited, terminated, or stopped.
        if (WIFEXITED(kos)) { //WEXITED returns true if child terminates normally from a call or return
            deletejob(jobs, process); // Delete the child from the job list
            printf("SIGCHLD_handler: Job [%d] (%i) deleted\n", jid, process);
            printf("SIGCHLD_handler: Job [%d] (%i) terminates OK (status %d)\n", jid, process, WEXITSTATUS(kos));
        }
        else if (WIFSIGNALED(kos)) { // returns true if child terminated cuz of uncaught signal
            deletejob(jobs,process);
            printf("sigchld_handler: Job [%d] (%d) deleted\n", jid, process);
            printf("Job [%d] (%d) terminated by signal %d\n", jid, process, WTERMSIG(kos));
        }
        else if (WIFSTOPPED(kos)) {     /*checks if child process that caused return is currently stopped */
            getjobpid(jobs, process)->state = ST; // Change job status to ST (stopped)
            printf("Job [%d] (%i) stopped by signal %d\n", jid, process, WSTOPSIG(kos));
        }
        
  }
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// sigint_handler - The kernel sends a SIGINT to the shell whenver the
//    user types ctrl-c at the keyboard.  Catch it and send it along
//    to the foreground job.  
//
void sigint_handler(int sig) 
{
    pid_t pid = fgpid(jobs); //finds first fg proccess
    if(pid != 0) //if we find fg process we kill it
    {
        kill(-pid, sig);   //negative kills off all the branches in fork
    }
    
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
//     the user types ctrl-z at the keyboard. Catch it and suspend the
//     foreground job by sending it a SIGTSTP.  
//
void sigtstp_handler(int sig) 
{
    pid_t pid = fgpid(jobs); //finds first fg proccess
    if(pid != 0) //if we find fg process we kill it
    {
        kill(-pid, sig);   
    }
  return;
}

/*********************
 * End signal handlers
 *********************/




