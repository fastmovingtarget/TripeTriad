#pragma once

public ref class RuleSet {
private:
	bool open = false;
	bool standard = true;
	bool same = false;
	bool wall = true; // Indicates if the wall rule is applied
	bool plus = true;
	bool cascade = true; // Indicates if the cascade rule is applied
public:
	//getters for the rule properties. Don't need setters as these are constants for the game rules
	bool isOpen() { return open; }
	bool isStandard() { return standard; }
	bool isSame() { return same; }
	bool isWall() { return wall; }
	bool isPlus() { return plus; }
	bool isCascade() { return cascade; }
};
