#pragma once

public ref class RuleSet {
private:
	bool open = false;
	bool standard = true;
	bool same = true;
public:
	bool isOpen() {
		return open; // Return the open rule status
	}
	bool isStandard() {
		return standard; // Return the standard rule status
	}
	bool isSame() {
		return same; // Return the same rule status
	}
};
