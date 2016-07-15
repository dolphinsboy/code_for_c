#include <stdio.h>
#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd *
getpwnam(const char *name)
{
    struct passwd *ptr;

    setpwent();

    while((ptr = getpwent()) != NULL)
        if (strcmp(name, ptr->pw_name) == 0){
            printf("%s %s %s\n", ptr->pw_name, ptr->pw_passwd, ptr->pw_dir);
            break;
        }
    endpwent();

    return(ptr);
}


int main()
{
    getpwnam("guosong");
}
