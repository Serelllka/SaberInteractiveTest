#include <stdio.h>
#include <math.h>

#define DELTA 1.0e-4

typedef struct
{
    double x, y, z;
} vec3;

void normalize(vec3* vector)
{
    double divider = sqrt(pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2));
    vector->x /= divider;
    vector->y /= divider;
    vector->z /= divider;
}

double vector_length(vec3 const vector)
{
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

void calculate_vector_product(vec3 vector1, vec3 vector2, vec3* product)
{
    product->x = vector1.y * vector2.z - vector1.z * vector2.y;
    product->y = vector1.z * vector2.x - vector1.x * vector2.z;
    product->z = vector1.x * vector2.y - vector1.y * vector2.x;
}

void calculate_normal(vec3 point1, vec3 point2, vec3 point3, vec3* result)
{
    vec3 vector1 = {point1.x - point3.x, point1.y - point3.y,  point1.z - point3.z};
    vec3 vector2 = {point1.x - point2.x, point1.y - point2.y,  point1.z - point2.z};
    calculate_vector_product(vector1, vector2, result);
    normalize(result);
}

void calculate_average_normal(int count, vec3* list_of_normals, vec3* result)
{
    result->x = 0, result->y = 0, result->z = 0;
    for (int i = 0; i < count; ++i)
    {
        result->x += (list_of_normals + i)->x;
        result->y += (list_of_normals + i)->y;
        result->z += (list_of_normals + i)->z;
    }
    normalize(result);
}

int face_contains_vert(const int* face, int count_of_verts, int vert)
{
    for (int i = 0; i < count_of_verts; ++i)
    {
        if (face[i] == vert)
        {
            return 1;
        }
    }
    return 0;
}

int contains_normal(vec3 const* list_of_normals, vec3 normal, int count)
{
    for (int i = 0; i < count; i++)
    {
        vec3 result;
        calculate_vector_product(list_of_normals[i], normal, &result);
        if (vector_length(result) < DELTA)
        {
            return 1;
        }
    }
    return 0;
}

void calc_mesh_normals(vec3* normals, const vec3* verts, const int* faces, int nverts, int nfaces)
{
    for (int i = 0; i < nverts; ++i)
    {
        int count_of_faces = 0;
        vec3 list_of_normals[nfaces];
        int offset = 0;
        for (int j = 0; j < nfaces; ++j)
        {
            if (face_contains_vert(faces + offset, 3, i))
            {
                calculate_normal(
                        verts[(faces + offset)[0]],
                        verts[(faces + offset)[1]],
                        verts[(faces + offset)[2]],
                        &list_of_normals[count_of_faces]);
                if (!contains_normal(list_of_normals, list_of_normals[count_of_faces], count_of_faces))
                {
                    count_of_faces++;
                }
            }
            offset += 3;
        }

        calculate_average_normal(count_of_faces, list_of_normals, normals + i);
    }
}

int main()
{
    vec3 points[] = {
            {0, 0, 0}, //0
            {0, 0, 1}, //1
            {0, 1, 0}, //2
            {0, 1, 1}, //3
            {1, 0, 0}, //4
            {1, 0, 1}, //5
            {1, 1, 0}, //6
            {1, 1, 1}, //7
    };

    int const faces[] = {
            6, 0, 4, // bottom
            0, 6, 2, //

            5, 1, 7, // top
            1, 3, 7, //

            4, 0, 1, // left
            1, 5, 4, //

            3, 2, 6, // right
            6, 7, 3, //

            3, 1, 0, // back
            3, 0, 2, //

            4, 5, 7, // front
            4, 7, 6, //
    };

    vec3 normals[8];
    calc_mesh_normals(normals, points, faces, 8, 12);

    for (int i = 0; i < 8; ++i)
    {
        printf("point: %f %f %f; normal: %f %f %f\n",
               points[i].x, points[i].y, points[i].z,
               normals[i].x, normals[i].y, normals[i].z);
    }

    return 0;
}

