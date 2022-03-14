#include "SystemDLL.h"
#include "Win32Caption.h"

namespace Win32 {
	Caption::Caption() {
	}

	Caption::~Caption() {
		for (std::list<CaptionButton*>::iterator iter = m_CaptionButtons.begin(); iter != m_CaptionButtons.end();) {
			SAFE_DELETE(*iter);

			iter = m_CaptionButtons.erase(iter);
		}
	}

	VOID Caption::AddCaptionButton(CaptionButton* button) {
		m_CaptionButtons.push_back(button);
	}
}
