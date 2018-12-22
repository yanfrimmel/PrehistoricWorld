#ifndef GRAPHICAL_API_H   /* Include guard */
#define GRAPHICAL_API_H
//flags: 1 = full screen
int showWindow(int window_width, int widow_height, int flags);  /* An example function declaration */
int initialize_sdl(void);
void quit_sdl(void** textures, void** renderers, void** window);

#endif 