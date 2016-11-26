#include "Effect.h"

float Distance2(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}
void CEffect::Func() {
	++var["moveCnt"];
	if (var["moveSpeed"]<= var["moveCnt"]) {
		var["moveCnt"] = 0;
		PlusY(1);
	}
	if (Distance2(GetX() + GetW() / 2, GetY() + GetH() / 2, MainChar->GetX() + MainChar->GetW() / 2, MainChar->GetY() + MainChar->GetH() / 2) >= 100) {
		this->Destory();
	}
}
