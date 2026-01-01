#pragma once
#include <cmath>

class Vec3D {
public:
    float x, y, z;

    Vec3D() : x(0), y(0), z(0) {}
    Vec3D(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3D operator+(const Vec3D& other) const {
        return Vec3D(x + other.x, y + other.y, z + other.z);
    }

    Vec3D operator-(const Vec3D& other) const {
        return Vec3D(x - other.x, y - other.y, z - other.z);
    }

    Vec3D operator*(float scalar) const {
        return Vec3D(x * scalar, y * scalar, z * scalar);
    }

    Vec3D operator/(float scalar) const {
        return Vec3D(x / scalar, y / scalar, z / scalar);
    }

    Vec3D& operator+=(const Vec3D& other) {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }

    Vec3D& operator-=(const Vec3D& other) {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }

    Vec3D& operator*=(float scalar) {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }

    Vec3D& operator/=(float scalar) {
        x /= scalar; y /= scalar; z /= scalar;
        return *this;
    }

    float lengthSquared() const {
        return x * x + y * y + z * z;
    }

    float length() const {
        return std::sqrt(lengthSquared());
    }
};

inline Vec3D normalize(const Vec3D& v) {
    float L = v.length();
    if (L <= 1e-6f) return {0,0,0};
    return v / L;
}

inline Vec3D clampMag(const Vec3D& v, float maxLen) {
    float L2 = v.lengthSquared();
    if (L2 <= maxLen*maxLen) return v;
    float L = std::sqrt(L2);
    return v * (maxLen / L);
}

inline float distSquared(const Vec3D& a, const Vec3D& b) {
    float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return dx*dx + dy*dy + dz*dz;
}