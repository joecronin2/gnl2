*This project has been created as part of the 42 curriculum by jcronin.*

## Description
```get_next_line()``` is similar to the libc function ```fgets()```, which reads a new line from a file on every consecutive call. 
```read()``` internally uses a file offset pointer (```struct file -> loff_t f_pos```)  that is updated on every call to read. Because a program has no idea on knowing where the next new line is going to be, get_next_line uses a fixed-size buffer to 'scan' chunks of the file until a newline is found. Only then does it return a full joined string, including the newline character. 
In the case that a file is invalid (e.g: fd < 0), NULL will be returned. In the case that a file has no remaining contents, NULL will also be returned. 

## Instructions
This project can be compiled with a C compiler like gcc, and the resulting binary can be linked against other programs. Other projects can include the ```get_next_line.h``` header file.

### Bonus
The bonus of this exercise requires only a single static variable to be used, and support the use of multiple open file descriptors to be used by get_next_line. 

### Resources
The main resource for this project was the man pages, especially for the read() function and system call. 
AI was used to better understand some concepts, but no code has been viewed, written, or debugged by AI.
