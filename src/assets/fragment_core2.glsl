#version 330 core
out vec4 FragColor;

in vec3 ourColor;

void main() {
    //FragColor = vec4(0.44f, 0.56f, 0.9f, 1.0f);
    FragColor = vec4(ourColor, 1.0);
}