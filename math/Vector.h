//
// Created by Jacob on 14.04.2020.
//

#ifndef RAYTRACER_VECTOR_H
#define RAYTRACER_VECTOR_H


class Vector {
public:
    Vector();

    Vector(float x);

    Vector(float x, float y);

    Vector(float x, float y, float z);

    void setX(float value);

    void setY(float value);

    void setZ(float value);

    void set(int position, float value);

    void scale(float value);

    void divide(float value);

    void normalize();

    void print();

    float getX();

    float getY();

    float getZ();

    float get(int position);

    float getLength();

    float dot(Vector const& obj);

    int sign(int pos);


    Vector cross(Vector const& obj);

    Vector getReflected(Vector normal);

    Vector getRefracted(Vector normal,float n1,float n2);

    Vector operator+(Vector const& obj);

    Vector operator-(Vector const& obj);

    /*/
    float operator * (Vector &obj);//  scalarmultiplication
    /*/
    Vector operator*(Vector const&obj);// cross product ^?
    /**/
    Vector operator*(float &obj);//scalar

private:
    float x;
    float y;
    float z;

};


#endif //RAYTRACER_VECTOR_H
