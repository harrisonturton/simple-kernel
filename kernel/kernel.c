void main() {
  // Create a pointer to a char, and point it to the first text cell
  // of video memory (i.e. the top-left of the screen)
  char* video_memory = (char*) 0xb8000;
  // At the address pointed to by vid_mem, store the character 'X'
  // i.e. Display 'X' in the top-left corner of the screen
  *video_memory = 'X';
}
