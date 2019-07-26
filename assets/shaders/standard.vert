layout(location = 0) in vec4 vert_pos;
  
uniform mat4 MVP;
  
void main() {
  gl_Position =  MVP * vert_pos;
}
