layout(location = 0) in vec4 vert_pos;
  
uniform mat4 matModel;
uniform mat4 matViewProjection;
  
void main() {
  gl_Position =  (matModel * matViewProjection) * vert_pos;
}