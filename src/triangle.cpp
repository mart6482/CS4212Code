#include "HitStructure.h"
#include "Triangle.h"

bool Triangle::intersect( const ray &r, float t_min, float t_max, hit_record& rec) const
{
    double a = this->vertex_a[0] - this->vertex_b[0];
    double b = this->vertex_a[1] - this->vertex_b[1];
    double c = this->vertex_a[2] - this->vertex_b[2];

    double d = this->vertex_a[0] - this->vertex_c[0];
    double e = this->vertex_a[1] - this->vertex_c[1];
    double f = this->vertex_a[2] - this->vertex_c[2];

    double g = r.getDirection()[0];
    double h = r.getDirection()[1];
    double i = r.getDirection()[2];

    double j = this->vertex_a[0] - r.getOrigin()[0];
    double k = this->vertex_a[1] - r.getOrigin()[1];
    double l = this->vertex_a[2] - r.getOrigin()[2];

    double ei_hf = e * i - h * f;
    double gf_di = g * f - d * i;
    double dh_eg = d * h - e * g;

    double M = a * ei_hf + b * gf_di + c* dh_eg;

    double t = -1.0, gamma = -1.0, beta = -1.0;

    beta = (j * ei_hf + k * gf_di + l * dh_eg) / M;
    gamma = (i*(a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / M;
    t = -(f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / M;
    double alpha = 1.0 - beta - gamma;

    if(t < 0.0) {
        return false;
    }
    if (gamma < 0.0 || gamma > 1.0) {
        return false;
    }
    if (beta < 0.0 || beta > 1.0 - gamma) {
        return false;
    }
    if (t < t_min || t > t_max) {
        return false;
    }
    return true;

    rec.t = t;
    rec.p = r.at(rec.t);
    rec.normal = normalize(cross(vertex_b - vertex_a, vertex_c - vertex_a));
}