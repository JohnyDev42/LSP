 #include <stdlib.h>
 #include <unistd.h>
 #include <stdio.h>
 #include <fcntl.h>
 #include <linux/fb.h>
 #include <sys/mman.h>
 #include <sys/stat.h> 
#include <sys/ioctl.h>
 #include <string.h>
 int main()
 {
     int fbfd = 0,ret,fd,oft;
     struct fb_var_screeninfo vinfo;
     struct fb_fix_screeninfo finfo;
     long int screensize = 0;
     char *fbp = 0,*bmp=0;
     int x = 0, y = 0;
     long int location = 0;
    char buff[4];
    char buf;
    struct stat	p;
     fd=open("NEW.bmp",O_RDWR,0666);
	if(fd==-1)
	{
		perror("open bmp");
		exit(0);
	}
	lseek(fd,54,SEEK_SET);
//	read(fd,buff,4);
//	oft=buff[0];
//	if(ret<0)
//	{
//		perror("read");
//		exit(0);
//	}
     // Open the file for reading and writing
     
     fstat(fd,&p);
    
     bmp=(char*)mmap(0,p.st_size-54,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
     printf("%d\n",p.st_size);
     if(bmp==MAP_FAILED)
     {
	     perror("bmp map");
	     exit(0);
     }
     fbfd = open("/dev/fb0", O_RDWR);
     if (fbfd == -1) {
         perror("Error: cannot open framebuffer device");
         exit(1);
     }
     printf("The framebuffer device was opened successfully.\n");

     // Get fixed screen information
     if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
         perror("Error reading fixed information");
         exit(2);
     }

     // Get variable screen information
     if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
         perror("Error reading variable information");
         exit(3);
     }

     printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

     // Figure out the size of the screen in bytes
     screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

     // Map the device to memory
     fbp = (char *)mmap(0,screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                        fbfd, 0);
     if ((int)fbp == -1) {
         perror("Error: failed to map framebuffer device to memory");
         exit(4);
     }
     printf("The framebuffer device was mapped to memory successfully.\n");
 // location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
  //                       (y+vinfo.yoffset) * finfo.line_length;

//	ftruncate(fbfd,p.st_size);
//	read()
	printf("Hi");
	ret=write(1,bmp,10);
	if(ret==-1)
	{
		perror("write");
		exit(0);
	}
	for(x=0;x<1366;x)
   //  memcpy(fbp,bmp,p.st_size);
     printf("Hello");
    // x = 100; y = 100;       // Where we are going to put the pixel

     // Figure out where in memory to put the pixel
    for (y = 0; y < 800; y++)
         for (x = 0; x < 1440; x++) {
             location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                        (y+vinfo.yoffset) * finfo.line_length;

             if (vinfo.bits_per_pixel == 32) {
//		     read(fd,&buf,1);
                 *(fbp + location) = 100;        // Some blue
  //               *(fbp + location + 1) = 25+(x-100)/2;     // A little green
  //               *(fbp + location + 2) = 20-(y-100)/5;    // A lot of red
    //             *(fbp + location + 3) = 0;      // No transparency
             } else  { //assume 16bpp
                 int b = 10;
                 int g = (x-100)/6;     // A little green
                 int r = 31-(y-100)/16;    // A lot of red
                 unsigned short int t = r<<11 | g << 5 | b;
                 *((unsigned short int*)(fbp + location)) = t;
             }

         }*/
     munmap(fbp, screensize);
     close(fbfd);
     return 0;
 }
