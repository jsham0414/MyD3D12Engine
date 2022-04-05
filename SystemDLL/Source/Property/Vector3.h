#pragma once

struct SYSTEM_DLL Vector3 : public Property {
private:
	XMFLOAT3 Vec;
public:
	float X() { Vec.x; }
	float Y() { Vec.y; }
	float Z() { Vec.z; }
};