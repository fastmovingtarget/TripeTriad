#pragma once

public ref class RuleSet {
private:
	bool open = false;
	bool standard = true;
	bool same = false;
	bool wall = true; // Indicates if the wall rule is applied
	bool plus = true;
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
	bool isWall() {
		return wall;
	}
	bool isPlus() {
		return plus;
	}
};
