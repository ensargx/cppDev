#include <iostream>

class Vector3D
{
public:
    int x, y, z;
    Vector3D(int x, int y, int z)
        : x(x), y(y), z(z)
    {
        std::cout << "Creating a Vector with x: " << x << ", y: " << y << ", z: " << z << "\n";
    }

    Vector3D operator+(const Vector3D& rhs)
    {
        return Vector3D(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    friend std::ostream& operator<<(std::ostream& out, const Vector3D& rhs)
    {
        out << "Vector(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
        return out;
    }

    operator int()
    {
        return x + y + z;
    }
};

int main()
{
    Vector3D vec1(1, 2, 3);
    Vector3D vec2(3, 2, 1);

    std::cout << vec1 << "\n";
    // Vector(1, 2, 3)
    std::cout << vec2 << "\n";
    // Vector(3, 2, 1)

    Vector3D vec3 = vec1 + vec2;
    std::cout << vec3 << "\n";
    // Vector(4, 4, 4)

    int scalar = vec3;
    std::cout << "Scalar: " << scalar << "\n";
    // Scalar: 12

    return 0;
}