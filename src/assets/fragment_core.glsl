#version 330 core
out vec4 FragColor;

void main() {
    // Utilisez la position du fragment pour générer des valeurs de couleur
    vec3 color = gl_FragCoord.xyz;

    // Normalisez les valeurs pour obtenir des couleurs entre 0 et 1
    color /= 800.0; // Utilisez une valeur appropriée pour normaliser en fonction de la résolution de votre fenêtre

    // Assignez la couleur au fragment
    FragColor = vec4(color, 1.0);
}