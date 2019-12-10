#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <string.h>
#include <sys/eventfd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
/*
 * Usage :                param1   param2   param3   param4
           1.read  : lfs  [PATH]   read     [addr]   [size] 
           2.write : lfs  [PATH]   write    [addr]   [data]
           3.iotcl : lfs  [PATH]   ioctl    [cmd]    [value]
*/

#define BUFFER_SIZE   100

enum cmd_type = {
        FS_READ = 0,
        FS_WRITE,
        FS_IOCTL
};

struct s_fs_priv = {
        char *path;
        int fd;
        int argc[4];
        char buff[BUFFER_SIZE];
};

struct s_fs_priv fs_priv = NULL; 


int fs_open(char *path)
{
        printf("fs_open Entry!\n");
        fs_priv.fd = open(path, O_RDWR);
        if ( fs_priv.fd < 0)
                printf("open %s file failed!\n",path);
        else 
                printf("open %s file successfully!\n",path);
        printf("fs_open Exit!\n");
}

int fs_close(void)
{
        printf("fs_read Entry!\n");   
        close(fs_priv.fs);
}

int fs_read(void)
{
        printf("fs_read Entry!\n");
        int count = 0;        
        count = read(fd_in, buff, 100) 
        printf("fs_read Exit!\n");               
}

int fs_write()
{
        printf("fs_write Entry!\n");         
        printf("fs_write Exit!\n");     
}

int fs_ioctl(int cmd)
{
        printf("fs_ioctl Entry!\n");         
        printf("fs_ioctl Exit!\n");     
}

int main(int argc, char **argv)
{
        if (argc < 4) {
                printf("input params num less than 4 \n");
                return -1;
        }        
        
        fs_priv.fd = -1;
        fs_priv.argc = argc;
        memset(fs_priv.buff, 0, sizeof(fs_priv.buff)/sizeof(fs_priv.buff[0]))
        
        

}
