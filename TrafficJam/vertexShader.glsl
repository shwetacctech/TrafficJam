attribute highp vec4 posAttr;
attribute lowp vec4 colAttr;
varying lowp vec4 col;
uniform highp mat4 matrix;
uniform float time; 

void main() {
    col = colAttr;
    
   
    float radius = 5.0; 
    float angularSpeed = 1.0; 
    float angle = time * angularSpeed; 

    float x = radius * cos(angle);
    float y = radius * sin(angle);
    
    vec4 translatedPosition = posAttr + vec4(x, 0, 0.0, 0.0);

    gl_Position = matrix * translatedPosition;
}
