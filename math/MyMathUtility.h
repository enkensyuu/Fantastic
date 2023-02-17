#pragma once

#include "Input.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

namespace MyMathUtility {

const float PI = 3.141592654f;

// ��x�N�g����Ԃ�
const Vector3 MySetVector3Zero();
// 2�x�N�g������v���Ă��邩���ׂ�
bool MyVector3Equal(const Vector3& v1, const Vector3& v2);
// �m����(����)�����߂�
float MyVector3Length(const Vector3& v);
// ���K������
Vector3& MyVector3Normalize(Vector3& v);
// ���ς����߂�
float MyVector3Dot(const Vector3& v1, const Vector3& v2);
// �O�ς����߂�
Vector3 MyVector3Cross(const Vector3& v1, const Vector3& v2);
//�x�����߂�
float GetDegree(float r);
//���W�A�������߂�
float GetRadian(float d);

// 2�����Z�q�I�[�o�[���[�h
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);

// �P�ʍs������߂�
Matrix4 MySetMatrix4Identity();
// �]�u�s������߂�
Matrix4 MyMatrix4Transpose(const Matrix4& m);
//�t�s������߂�
Matrix4 MyMatrix4Inverse(const Matrix4& m, float* det = nullptr);

  // �g��k���s��̍쐬
Matrix4 MyGenMatrix4Scaling(Vector3 scale);

// ��]�s��̍쐬
Matrix4 MyGenMatrix4RotationX(float angle);
Matrix4 MyGenMatrix4RotationY(float angle);
Matrix4 MyGenMatrix4RotationZ(float angle);

//�����ς݉�]�s��̍쐬
Matrix4 MySynMatrix4Rotation(Vector3 rotation);

// ���s�ړ��s��̍쐬
Matrix4 MyGenMatrix4Translation(Vector3 translation);

//���[���h�s��̍쐬
Matrix4 MySynMatrix4WorldTransform(WorldTransform worldTransform);

//���_�ړ��x�N�g����ύX
Vector3 MyChanVector3ViewEye(Input* key);
//�����_�ړ��x�N�g����ύX
Vector3 MyChanVector3ViewTarget(Input* key);
//������x�N�g����ύX
Vector3 MyChanVector3ViewUp(Input* key, float& upAngle);
// FoV�ύX
float MyChanProjectionFovAngleY(Input* key, float fovY);
// �j�A�N���b�v�����̕ύX
float MyChanProfectionNearClipZ(Input* key, float nearZ);

// �r���[�s��̍쐬
Matrix4 MyMatrix4LookAtLH(const Vector3& eye, const Vector3& target, const Vector3& up);
// ���s���e�s��̍쐬
Matrix4 MyMatrix4Orthographic(
  float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
// �������e�s��̍쐬
Matrix4 MyMatrix4Perspective(float fovAngleY, float aspectRatio, float nearZ, float farZ);

// ���W�ϊ��iw���Z�Ȃ��j
Vector3 MyVector3Transform(const Vector3& v, const Matrix4& m);
// ���W�ϊ��iw���Z����j
Vector3 MyVector3TransformCoord(const Vector3& v, const Matrix4& m);
// �x�N�g���ϊ�
Vector3 MyVector3TransformNormal(Vector3 vector, Matrix4 matrix);

// 2�����Z�q�I�[�o�[���[�h
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
Vector3 operator*(const Vector3& v, const Matrix4& m);

} // namespace MyMathUtility
