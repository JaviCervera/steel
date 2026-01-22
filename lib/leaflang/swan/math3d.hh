#ifndef SWAN_MATH3D_INCLUDED
#define SWAN_MATH3D_INCLUDED

#include <math.h>
#include <string.h>

namespace swan
{
  // forward declaration
  struct vec2_t;
  struct vec3_t;
  struct vec4_t;
  struct quat_t;
  struct mat4_t;

  inline float deg2rad(float deg) { return deg * 0.0174532925f; }
  inline float rad2deg(float rad) { return rad * 57.2957795f; }

  struct vec2_t
  {
    float x, y;
    vec2_t(float x = 0, float y = 0) : x(x), y(y) {}
    vec2_t(const vec2_t& other) : x(other.x), y(other.y) {}
    vec2_t(const vec3_t& other);
    bool operator==(const vec2_t& other) const { return x == other.x && y == other.y; }
    bool operator!=(const vec2_t& other) const { return x != other.x || y != other.y; }
    vec2_t& operator=(const vec2_t& other) { x = other.x; y = other.y; return *this; }
    vec2_t operator+(const vec2_t& other) const { return vec2_t(x + other.x, y + other.y); }
    vec2_t operator-(const vec2_t& other) const { return vec2_t(x - other.x, y - other.y); }
    vec2_t operator*(const vec2_t& other) const { return vec2_t(x * other.x, y * other.y); }
    vec2_t operator/(const vec2_t& other) const { return vec2_t(x / other.x, y / other.y); }
    vec2_t operator+(float scalar) const { return vec2_t(x + scalar, y + scalar); }
    vec2_t operator-(float scalar) const { return vec2_t(x - scalar, y - scalar); }
    vec2_t operator*(float scalar) const { return vec2_t(x * scalar, y * scalar); }
    vec2_t operator/(float scalar) const { return vec2_t(x / scalar, y / scalar); }
    vec2_t& operator+=(const vec2_t& other) { x += other.x; y += other.y; return *this; }
    vec2_t& operator-=(const vec2_t& other) { x -= other.x; y -= other.y; return *this; }
    vec2_t& operator*=(const vec2_t& other) { x *= other.x; y *= other.y; return *this; }
    vec2_t& operator/=(const vec2_t& other) { x /= other.x; y /= other.y; return *this; }
    vec2_t& operator+=(float scalar) { x += scalar; y += scalar; return *this; }
    vec2_t& operator-=(float scalar) { x -= scalar; y -= scalar; return *this; }
    vec2_t& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    vec2_t& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }
    float sqlength() const { return dot(*this); }
    float length() const { return sqrt(sqlength()); }
    vec2_t norm() const;
    float dot(const vec2_t& other) const { return x * other.x + y * other.y; }
    vec2_t mix(const vec2_t& other, float t) const { return *this + (other - *this) * t; }
  };

  inline vec2_t vec2_t::norm() const
  {
    const float ln = length();
    const float iln = ln > 0 ? 1.0f / ln : 0;
    return *this * iln;
  }

  struct vec3_t
  {
    float x, y, z;
    vec3_t(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    vec3_t(const vec2_t& other, float z) : x(other.x), y(other.y), z(z) {}
    vec3_t(const vec3_t& other) : x(other.x), y(other.y), z(other.z) {}
    vec3_t(const vec4_t& other);
    bool operator==(const vec3_t& other) const { return x == other.x && y == other.y && z == other.z; }
    bool operator!=(const vec3_t& other) const { return x != other.x || y != other.y || z != other.z; }
    vec3_t& operator=(const vec3_t& other) { x = other.x; y = other.y; z = other.z; return *this; }
    vec3_t operator+(const vec3_t& other) const { return vec3_t(x + other.x, y + other.y, z + other.z); }
    vec3_t operator-(const vec3_t& other) const { return vec3_t(x - other.x, y - other.y, z - other.z); }
    vec3_t operator*(const vec3_t& other) const { return vec3_t(x * other.x, y * other.y, z * other.z); }
    vec3_t operator/(const vec3_t& other) const { return vec3_t(x / other.x, y / other.y, z / other.z); }
    vec3_t operator+(float scalar) const { return vec3_t(x + scalar, y + scalar, z + scalar); }
    vec3_t operator-(float scalar) const { return vec3_t(x - scalar, y - scalar, z - scalar); }
    vec3_t operator*(float scalar) const { return vec3_t(x * scalar, y * scalar, z * scalar); }
    vec3_t operator/(float scalar) const { return vec3_t(x / scalar, y / scalar, z / scalar); }
    vec3_t& operator+=(const vec3_t& other) { x += other.x; y += other.y; z += other.z; return *this; }
    vec3_t& operator-=(const vec3_t& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
    vec3_t& operator*=(const vec3_t& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
    vec3_t& operator/=(const vec3_t& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
    vec3_t& operator+=(float scalar) { x += scalar; y += scalar; z += scalar; return *this; }
    vec3_t& operator-=(float scalar) { x -= scalar; y -= scalar; z -= scalar; return *this; }
    vec3_t& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
    vec3_t& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }
    float sqlength() const { return dot(*this); }
    float length() const { return sqrt(sqlength()); }
    vec3_t norm() const;
    float dot(const vec3_t& other) const { return x * other.x + y * other.y + z * other.z; }
    vec3_t cross(const vec3_t& other) const { return vec3_t(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x); }
    vec3_t rad() const { return vec3_t(deg2rad(x), deg2rad(y), deg2rad(z)); }
    vec3_t deg() const { return vec3_t(rad2deg(x), rad2deg(y), rad2deg(z)); }
    vec3_t mix(const vec3_t& other, float t) const { return *this + (other - *this); }
  };

  inline vec3_t vec3_t::norm() const
  {
    const float ln = length();
    const float iln = ln > 0 ? 1.0f / ln : 0;
    return *this * iln;
  }

  struct vec4_t
  {
    float x, y, z, w;
    vec4_t(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w) {}
    vec4_t(const vec3_t& other, float w) : x(other.x), y(other.y), z(other.z), w(w) {}
    vec4_t(const vec4_t& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
    bool operator==(const vec4_t& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
    bool operator!=(const vec4_t& other) const { return x != other.x || y != other.y || z != other.z || w != other.w; }
    vec4_t& operator=(const vec4_t& other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }
    vec4_t operator+(const vec4_t& other) const { return vec4_t(x + other.x, y + other.y, z + other.z, w + other.w); }
    vec4_t operator-(const vec4_t& other) const { return vec4_t(x - other.x, y - other.y, z - other.z, w - other.w); }
    vec4_t operator*(const vec4_t& other) const { return vec4_t(x * other.x, y * other.y, z * other.z, w * other.w); }
    vec4_t operator/(const vec4_t& other) const { return vec4_t(x / other.x, y / other.y, z / other.z, w / other.w); }
    vec4_t operator+(float scalar) const { return vec4_t(x + scalar, y + scalar, z + scalar, w + scalar); }
    vec4_t operator-(float scalar) const { return vec4_t(x - scalar, y - scalar, z - scalar, w - scalar); }
    vec4_t operator*(float scalar) const { return vec4_t(x * scalar, y * scalar, z * scalar, w * scalar); }
    vec4_t operator/(float scalar) const { return vec4_t(x / scalar, y / scalar, z / scalar, w / scalar); }
    vec4_t& operator+=(const vec4_t& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
    vec4_t& operator-=(const vec4_t& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
    vec4_t& operator*=(const vec4_t& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
    vec4_t& operator/=(const vec4_t& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }
    vec4_t& operator+=(float scalar) { x += scalar; y += scalar; z += scalar; w += scalar; return *this; }
    vec4_t& operator-=(float scalar) { x -= scalar; y -= scalar; z -= scalar; w -= scalar; return *this; }
    vec4_t& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
    vec4_t& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }
    float length() const { return sqrt(dot(*this)); }
    vec4_t norm() const;
    float dot(const vec4_t& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }
    vec4_t mix(const vec4_t& other, float t) const { return *this + (other - *this) * t; }
  };

  inline vec4_t vec4_t::norm() const
  {
    const float ln = length();
    const float iln = ln > 0 ? 1.0f / ln : 0;
    return *this * iln;
  }

  inline vec2_t::vec2_t(const vec3_t& other) : x(other.x), y(other.y) {}
  inline vec3_t::vec3_t(const vec4_t& other) : x(other.x), y(other.y), z(other.z) {}

  struct quat_t
  {
    float w, x, y, z;
    quat_t(float w = 1, float x = 0, float y = 0, float z = 0) : w(w), x(x), y(y), z(z) {}
    quat_t(const quat_t& q) : w(q.w), x(q.x), y(q.y), z(q.z) {}
    quat_t(float angle, const vec3_t& axis);
    quat_t(const vec3_t& euler);
    bool operator==(const quat_t& other) const { return w == other.w && x == other.x && y == other.y && z == other.z; }
    quat_t& operator=(const quat_t& other) { w = other.w; x = other.x; y = other.y; z = other.z; return *this; }
    quat_t operator+(const quat_t& other) const { return quat_t(w+other.w, x+other.x, y+other.y, z+other.z); }
    quat_t operator*(const quat_t& other) const;
    vec3_t operator*(const vec3_t& vec) const { quat_t vq(0, vec.x, vec.y, vec.z); quat_t rq = *this * vq * conj(); return vec3_t(rq.x, rq.y, rq.z); }
    quat_t operator*(float scale) const { return quat_t(w*scale, x*scale, y*scale, z*scale); }
    quat_t operator/(float scale) const { return quat_t(w/scale, x/scale, y/scale, z/scale); }
    quat_t norm() const;
    quat_t conj() const { return quat_t(w, -x, -y, -z); }
    float angle() const { return acos(w) * 2.0f; }
    vec3_t axis() const { float scale = sqrt(x*x + y*y + z*z); float invscale = 1.0f / (scale != 0.0f ? scale : 0.00001f); return vec3_t(x * invscale, y * invscale, z * invscale); }
    vec3_t euler() const;
    quat_t lerp(const quat_t& other, float t) const { return (*this*(1-t) + other*t).norm(); }
    quat_t slerp(const quat_t& other, float t) const;
    float dot(const quat_t& other) const { return w*other.w + x*other.x + y*other.y + z*other.z; }
  };

  inline quat_t::quat_t(float angle, const vec3_t& axis)
  {
    vec3_t naxis = axis.norm();
    float s = sin(angle);
    w = cos(angle * 0.5f);
    x = naxis.x * s;
    y = naxis.y * s;
    z = naxis.z * s;
  }

  inline quat_t::quat_t(const vec3_t& euler)
  {
    float halfx = euler.x * 0.5f;
    float halfy = euler.y * 0.5f;
    float halfz = euler.z * 0.5f;
    float sinpitch = sin(halfx);
    float sinyaw = sin(halfy);
    float sinroll = sin(halfz);
    float cospitch = cos(halfx);
    float cosyaw = cos(halfy);
    float cosroll = cos(halfz);
    w = cospitch * cosyaw * cosroll + sinpitch * sinyaw * sinroll;
    x = sinpitch * cosyaw * cosroll - cospitch * sinyaw * sinroll;
    y = cospitch * sinyaw * cosroll + sinpitch * cosyaw * sinroll;
    z = cospitch * cosyaw * sinroll - sinpitch * sinyaw * cosroll;
  }

  inline quat_t quat_t::operator*(const quat_t& other) const
  {
    return quat_t(w*other.w - x*other.x - y*other.y - z*other.z,
                  w*other.x + x*other.w + y*other.z - z*other.y,
                  w*other.y + y*other.w + z*other.x - x*other.z,
                  w*other.z + z*other.w + x*other.y - y*other.x);
  }

  inline quat_t quat_t::norm() const
  {
    float mag2 = w*w + x*x + y*y + z*z;
    if (mag2 > 0.00001f && fabs(mag2 - 1.0f) > 0.00001f)
    {
      float invmag = 1.0f / sqrt(mag2);
      return quat_t(w * invmag, x * invmag, y * invmag, z * invmag);
    }
    else
    {
      return *this;
    }
  }

  inline vec3_t quat_t::euler() const
  {
    float pitch = atan2(2 * (y*z + w*x), w*w - x*x - y*y + z*z);
    float yaw = asin(-2 * (x*z - w*y));
    float roll = atan2(2 * (x*y + w*z), w*w + x*x - y*y - z*z);
    return vec3_t(pitch, yaw, roll);
  }

  inline quat_t quat_t::slerp(const quat_t& other, float t) const
  {
    quat_t q;
    float d = dot(other);
    if (d < 0.0f)
    {
      d *= -1;
      q = other * -1;
    }
    else
    {
      q = other;
    }
    if (d < 0.95f)
    {
      float angle = acos(d);
      return (*this * sin(angle*(1-t)) + q*sin(angle*t)) / sin(angle);
    }
    else
    {
      return lerp(q, t);
    }
  }

  struct mat4_t
  {
    float m[16];
    mat4_t(float id = 1) { memset(m, 0, sizeof(m)); m[0] = m[5] = m[10] = m[15] = id; }
    mat4_t(const mat4_t& other) { memcpy(m, other.m, sizeof(m)); }
    mat4_t(const float* values) { memcpy(this->m, values, sizeof(this->m)); }
    bool operator==(const mat4_t& other) const { for ( size_t i = 0; i < 16; ++i ) if ( m[i] != other.m[i] ) return false; return true; }
    mat4_t& operator=(const mat4_t& other) { memcpy(m, other.m, sizeof(m)); return *this; }
    mat4_t operator+(const mat4_t& other) const { mat4_t mat(*this); for ( size_t i = 0; i < 16; ++i ) mat.m[i] += other.m[i]; return mat; }
    mat4_t operator-(const mat4_t& other) const { mat4_t mat(*this); for ( size_t i = 0; i < 16; ++i ) mat.m[i] -= other.m[i]; return mat; }
    mat4_t operator*(const mat4_t& other) const;
    vec4_t operator*(const vec4_t& vec) const { mat4_t mat; mat.sett(vec); mat = *this * mat; return vec4_t(mat.m[12], mat.m[13], mat.m[14], mat.m[15]); }
    mat4_t& operator+=(const mat4_t& other) { *this = *this + other; return *this; }
    mat4_t& operator-=(const mat4_t& other) { *this = *this - other; return *this; }
    mat4_t& operator*=(const mat4_t& other) { *this = *this * other; return *this; }
    const float& operator[](size_t pos) const { return m[pos]; }
    float& operator[](size_t pos) { return m[pos]; }
    float get(size_t col, size_t row) const { return m[col*4 + row]; }
    void set(size_t col, size_t row, float val) { m[col*4 + row] = val; }
    mat4_t translate(const vec3_t& trans) const { mat4_t mt; mt.sett(vec4_t(trans, 1)); return *this * mt; }
    mat4_t rotate(float angle, const vec3_t& axis) const { mat4_t mr; mr.setr(angle, axis); return *this * mr; }
    mat4_t scale(const vec3_t& scale) const { mat4_t ms; ms.sets(scale); return *this * ms; }
    mat4_t trans() const { mat4_t mat; for ( size_t r = 0; r < 4; ++r ) for ( size_t c = 0; c < 4; ++c ) mat.set(c, r, get(r, c)); return mat; }
    mat4_t inv() const;
    static mat4_t ortho_lh(float left, float right, float bottom, float top, float near, float far);
    static mat4_t frustum_lh(float left, float right, float bottom, float top, float near, float far);
    static mat4_t perspective_lh(float fovy, float aspect, float near, float far);
    static mat4_t lookat_lh(const vec3_t& pos, const vec3_t& look, const vec3_t& up);
    static mat4_t ortho_rh(float left, float right, float bottom, float top, float near, float far);
    static mat4_t frustum_rh(float left, float right, float bottom, float top, float near, float far);
    static mat4_t perspective_rh(float fovy, float aspect, float near, float far);
    static mat4_t lookat_rh(const vec3_t& pos, const vec3_t& look, const vec3_t& up);
  private:
    void sett(const vec4_t& v) { m[12] = v.x; m[13] = v.y; m[14] = v.z; m[15] = v.w; }
    void setr(float angle, const vec3_t& axis);
    void sets(const vec3_t& scale) { m[0] = scale.x; m[5] = scale.y; m[10] = scale.z; }
  };

  inline mat4_t mat4_t::operator*(const mat4_t& other) const
  {
    mat4_t mat;
    for (size_t i = 0; i < 4; ++i)
    {
      float a0 = m[i];
      float a1 = m[i+4];
      float a2 = m[i+8];
      float a3 = m[i+12];
      mat.m[i] = a0*other.m[0] + a1*other.m[1] + a2*other.m[2] + a3*other.m[3];
      mat.m[i+4] = a0*other.m[4] + a1*other.m[5] + a2*other.m[6] + a3*other.m[7];
      mat.m[i+8] = a0*other.m[8] + a1*other.m[9] + a2*other.m[10] + a3*other.m[11];
      mat.m[i+12] = a0*other.m[12] + a1*other.m[13] + a2*other.m[14] + a3*other.m[15];
    }
    return mat;
  }

  inline mat4_t mat4_t::inv() const
  {
    mat4_t inv;
    inv[ 0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
    inv[ 4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
    inv[ 8] =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
    inv[12] = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
    inv[ 1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
    inv[ 5] =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
    inv[ 9] = -m[0] * m[ 9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[ 9];
    inv[13] =  m[0] * m[ 9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[ 9];
    inv[ 2] =  m[1] * m[ 6] * m[15] - m[1] * m[ 7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[ 7] - m[13] * m[3] * m[ 6];
    inv[ 6] = -m[0] * m[ 6] * m[15] + m[0] * m[ 7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[ 7] + m[12] * m[3] * m[ 6];
    inv[10] =  m[0] * m[ 5] * m[15] - m[0] * m[ 7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[ 7] - m[12] * m[3] * m[ 5];
    inv[14] = -m[0] * m[ 5] * m[14] + m[0] * m[ 6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[ 6] + m[12] * m[2] * m[ 5];
    inv[ 3] = -m[1] * m[ 6] * m[11] + m[1] * m[ 7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[ 9] * m[2] * m[ 7] + m[ 9] * m[3] * m[ 6];
    inv[ 7] =  m[0] * m[ 6] * m[11] - m[0] * m[ 7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[ 8] * m[2] * m[ 7] - m[ 8] * m[3] * m[ 6];
    inv[11] = -m[0] * m[ 5] * m[11] + m[0] * m[ 7] * m[ 9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[ 9] - m[ 8] * m[1] * m[ 7] + m[ 8] * m[3] * m[ 5];
    inv[15] =  m[0] * m[ 5] * m[10] - m[0] * m[ 6] * m[ 9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[ 9] + m[ 8] * m[1] * m[ 6] - m[ 8] * m[2] * m[ 5];
    float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    if (fabs(det) <= 0.00001f) return mat4_t();
    float invdet = 1.0f / det;
    for (size_t i = 0; i < 16; ++i) inv[i] *= invdet;
    return inv;
  }

  inline mat4_t mat4_t::ortho_lh(float left, float right, float bottom, float top, float near, float far)
  {
    float a = 2.0f / (right - left);
    float b = 2.0f / (top - bottom);
    float c = 2.0f / (far - near);
    float tx = (left+right) / (left-right);
    float ty = (bottom+top) / (bottom-top);
    float tz = (near+far) / (near-far);
    float m[] = {a, 0, 0, 0,  0, b, 0, 0,  0, 0, c, 0,  tx, ty, tz, 1};
    return mat4_t(m);
  }

  inline mat4_t mat4_t::frustum_lh(float left, float right, float bottom, float top, float near, float far)
  {
    mat4_t m;
    m.m[0]  = 2 * near / (right - left);
    m.m[5]  = 2 * near / (top - bottom);
    m.m[8]  = (left + right) / (left - right);
    m.m[9]  = (bottom + top) / (bottom - top);
    m.m[10] = (far + near) / (far - near);
    m.m[11] = 1;
    m.m[14] = (2 * near * far) / (near - far);
    m.m[15] = 0;
    return m;
  }

  inline mat4_t mat4_t::perspective_lh(float fovy, float aspect, float near, float far)
  {
    float height = near * tan(fovy*0.5f);
    float width = height * aspect;
    return frustum_lh(-width, width, -height, height, near, far);
  }

  inline mat4_t mat4_t::lookat_lh(const vec3_t& pos, const vec3_t& look, const vec3_t& up)
  {
    vec3_t z = (look - pos).norm();
    vec3_t x = up.cross(z);
    vec3_t y = z.cross(x);
    x = x.norm();
    y = y.norm();
    float m[] = {x.x, y.x, z.x, 0,  x.y, y.y, z.y, 0,  x.z, y.z, z.z, 0,  0, 0, 0, 1};
    return mat4_t(m).translate(pos * -1);
  }

  inline mat4_t mat4_t::ortho_rh(float left, float right, float bottom, float top, float near, float far)
  {
    float a = 2.0f / (right - left);
    float b = 2.0f / (top - bottom);
    float c = 2.0f / (near - far);
    float tx = (left+right) / (left-right);
    float ty = (bottom+top) / (bottom-top);
    float tz = (near+far) / (near-far);
    float m[] = {a, 0, 0, 0,  0, b, 0, 0,  0, 0, c, 0,  tx, ty, tz, 1};
    return mat4_t(m);
  }

  inline mat4_t mat4_t::frustum_rh(float left, float right, float bottom, float top, float near, float far)
  {
    mat4_t m;
    m.m[0]  = 2 * near / (right - left);
    m.m[5]  = 2 * near / (top - bottom);
    m.m[8]  = (right + left) / (right - left);
    m.m[9]  = (top + bottom) / (top - bottom);
    m.m[10] = (near + far) / (near - far);
    m.m[11] = -1;
    m.m[14] = (2 * near * far) / (near - far);
    m.m[15] = 0;
    return m;
  }

  inline mat4_t mat4_t::perspective_rh(float fovy, float aspect, float near, float far)
  {
    float height = near * tan(fovy*0.5f);
    float width = height * aspect;
    return frustum_rh(-width, width, -height, height, near, far);
  }

  inline mat4_t mat4_t::lookat_rh(const vec3_t& pos, const vec3_t& look, const vec3_t& up)
  {
    vec3_t z = (pos - look).norm();
    vec3_t x = up.cross(z);
    vec3_t y = z.cross(x);
    x = x.norm();
    y = y.norm();
    float m[] = {x.x, y.x, z.x, 0,  x.y, y.y, z.y, 0,  x.z, y.z, z.z, 0,  0, 0, 0, 1};
    return mat4_t(m).translate(pos * -1);
  }

  inline void mat4_t::setr(float angle, const vec3_t& axis)
  {
    float c = cos(angle);
    float s = sin(angle);
    float xx = axis.x * axis.x;
    float xy = axis.x * axis.y;
    float xz = axis.x * axis.z;
    float yy = axis.y * axis.y;
    float yz = axis.y * axis.z;
    float zz = axis.z * axis.z;
    m[0] = xx * (1 - c) + c;
    m[1] = xy * (1 - c) + axis.z * s;
    m[2] = xz * (1 - c) - axis.y * s;
    m[4] = xy * (1 - c) - axis.z * s;
    m[5] = yy * (1 - c) + c;
    m[6] = yz * (1 - c) + axis.x * s;
    m[8] = xz * (1 - c) + axis.y * s;
    m[9] = yz * (1 - c) - axis.x * s;
    m[10] = zz * (1 - c) + c;
  }
} // namespace swan

#endif // SWAN_MATH3D_INCLUDED
