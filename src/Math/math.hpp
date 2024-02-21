#include <iostream>
#include <cmath>

class Vec4 {
    public : 
        float x, y, z, w;

        Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        void translate(float tx, float ty, float tz) {
            x += tx;
            y += ty;
            z += tz;
        }
};

class Vec3 {
    public:
        float x, y, z;

        // Constructeur
        Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

        // Affichage
        void display() {
            std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
        }

            // Produit vectoriel
        Vec3 cross(const Vec3& other) const {
            return Vec3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            );
        }

        // Produit scalaire
        float dot(const Vec3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        // Norme du vecteur
        float length() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        // Normalisation du vecteur
        Vec3 normalize() const {
            float len = length();
            if (len != 0.0f) {
                return Vec3(x / len, y / len, z / len);
            }
            return *this;
        }
};

class Mat4 {
    public:
        float mat[4][4];

        Mat4(float homogene = 1.0f) {
            mat[0][0] = 1.0f; mat[0][1] = 0.0f; mat[0][2] = 0.0f; mat[0][3] = 0.0f;
            mat[1][0] = 0.0f; mat[1][1] = 1.0f; mat[1][2] = 0.0f; mat[1][3] = 0.0f;
            mat[2][0] = 0.0f; mat[2][1] = 0.0f; mat[2][2] = 1.0f; mat[2][3] = 0.0f;
            mat[3][0] = 0.0f; mat[3][1] = 0.0f; mat[3][2] = 0.0f; mat[3][3] = homogene;
        }

        friend std::ostream& operator<<(std::ostream& os, const Mat4& obj) {
            for (int i = 0; i < 4; i++) {
                os << "[ ";
                for (int j = 0; j < 4; j++) {
                    os << obj.mat[i][j];
                    if (j < 3) {
                        os << ", ";
                    }
                }
                os << " ]" << std::endl;
            }
            return os;
        }
    
        void translate(Vec3 vector) {
            mat[0][3] = vector.x;
            mat[1][3] = vector.y;
            mat[2][3] = vector.z;
        }


        static Mat4 rotate(const Mat4& matrix, float angle, float x, float y, float z) {
            Mat4 result(1.0f);

            float radians = angle * (M_PI / 180.0f);
            float c = cos(radians);
            float s = sin(radians);
            float one_minus_c = 1.0f - c;

            float xy = x * y;
            float xz = x * z;
            float yz = y * z;
            float xs = x * s;
            float ys = y * s;
            float zs = z * s;

            float f00 = x * x * one_minus_c + c;
            float f01 = xy * one_minus_c + zs;
            float f02 = xz * one_minus_c - ys;
            float f10 = xy * one_minus_c - zs;
            float f11 = y * y * one_minus_c + c;
            float f12 = yz * one_minus_c + xs;
            float f20 = xz * one_minus_c + ys;
            float f21 = yz * one_minus_c - xs;
            float f22 = z * z * one_minus_c + c;

            result.mat[0][0] = matrix.mat[0][0] * f00 + matrix.mat[1][0] * f01 + matrix.mat[2][0] * f02;
            result.mat[0][1] = matrix.mat[0][1] * f00 + matrix.mat[1][1] * f01 + matrix.mat[2][1] * f02;
            result.mat[0][2] = matrix.mat[0][2] * f00 + matrix.mat[1][2] * f01 + matrix.mat[2][2] * f02;
            result.mat[0][3] = matrix.mat[0][3] * f00 + matrix.mat[1][3] * f01 + matrix.mat[2][3] * f02;
            result.mat[1][0] = matrix.mat[0][0] * f10 + matrix.mat[1][0] * f11 + matrix.mat[2][0] * f12;
            result.mat[1][1] = matrix.mat[0][1] * f10 + matrix.mat[1][1] * f11 + matrix.mat[2][1] * f12;
            result.mat[1][2] = matrix.mat[0][2] * f10 + matrix.mat[1][2] * f11 + matrix.mat[2][2] * f12;
            result.mat[1][3] = matrix.mat[0][3] * f10 + matrix.mat[1][3] * f11 + matrix.mat[2][3] * f12;
            result.mat[2][0] = matrix.mat[0][0] * f20 + matrix.mat[1][0] * f21 + matrix.mat[2][0] * f22;
            result.mat[2][1] = matrix.mat[0][1] * f20 + matrix.mat[1][1] * f21 + matrix.mat[2][1] * f22;
            result.mat[2][2] = matrix.mat[0][2] * f20 + matrix.mat[1][2] * f21 + matrix.mat[2][2] * f22;
            result.mat[2][3] = matrix.mat[0][3] * f20 + matrix.mat[1][3] * f21 + matrix.mat[2][3] * f22;

            return result;
        }

        void scale(const Vec3 factors) {
            mat[0][0] *= factors.x;
            mat[1][1] *= factors.y;
            mat[2][2] *= factors.z;
        }

        float* GetDataPtr() {
            return &mat[0][0];
        }
};