#include "systemcalls.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/wait.h"
#include "fcntl.h"
#include "errno.h"
#include "string.h"

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

/*
 * TODO  add your code here
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/
    int ret;

    ret = system(cmd);
    if (ret==-1) {
        return false;
    }

    return true;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    // command[count] = command[count];

/*
 * TODO:
 *   Execute a system command by calling fork, execv(),
 *   and wait instead of system (see LSP page 161).
 *   Use the command[0] as the full path to the command to execute
 *   (first argument to execv), and use the remaining arguments
 *   as second argument to the execv() command.
 *
*/

    va_end(args);
    int status;
    pid_t pid;
    int ret;
    
    fflush(stdout);
    pid = fork();
    if (pid==-1) {
        return -1;
    }
    if (pid==0) {
        int cret;

        printf("Child's parent is %d.\n", getppid());
        printf("Child pid: %d.\n", getpid());
        printf("Child is trying to run %s %s %s.\n", command[0], command[1], command[2]);
        cret = execve (command[0], command, NULL);
        if (cret==-1) {
            printf("ppid: %d\tpid:%d\n", getppid(), getpid());
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    printf("I am the parent: %d.\n", getpid());
    ret = wait (&status);

    if (ret==-1) {
        if (errno == EINVAL){
            printf("Caught a bad one: (Error: %s)\n", strerror(errno));
        }
        return false;
    }
    if (WIFEXITED(status)) {
        printf("This parent is %d.\n", getpid());
        printf("Child returned status do_exec: %d.\n", WEXITSTATUS(status));
        printf("Command was %s %s %s.\n", command[0], command[1], command[2]);
        if (WEXITSTATUS(status)){
            printf("WEXITSTATUS(status) is %d\n", WEXITSTATUS(status));
             return false;
        }
    }
    
    return true;
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    // command[count] = command[count];


/*
 * TODO
 *   Call execv, but first using https://stackoverflow.com/a/13784315/1446624 as a refernce,
 *   redirect standard out to a file specified by outputfile.
 *   The rest of the behaviour is same as do_exec()
 *
*/

    va_end(args);

    int status;
    pid_t pid;
    int ret;
    int fd = open(outputfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        abort();
    }

    fflush(stdout);
    pid = fork();
    if (pid==-1) {
        return -1;
    }
    if (pid==0) {
        if (dup2(fd, 1) < 0) { 
            perror("dup2");
            printf("Aborting ...");
            abort(); 
        }
        execvp (command[0], command);
        abort();
    }
    ret = wait (&status);

    if (ret==-1) {
        return false;
    }
    else if (WIFEXITED(status)) {
        if (WEXITSTATUS(status)){
            printf("WEXITSTATUS(status) is %d\n", WEXITSTATUS(status));
             return false;
        } else {
            return true;
        }
    }
    


    return true;
}
