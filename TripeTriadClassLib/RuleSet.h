#pragma once

public ref class RuleSet {
private:
	bool open = false;
	bool standard = true;
	bool same = false;
	bool wall = false; // Indicates if the wall rule is applied
	bool plus = false;
	bool cascade = false; // Indicates if the cascade rule is applied
public:
	RuleSet(bool opn, bool std, bool sme, bool wll, bool pls, bool csd) : 
		open(opn), standard(std), same(sme), wall(wll), plus(pls), cascade(csd) {}
	RuleSet() {};
	//getters for the rule properties. Don't need setters as these are constants for the game rules
	bool isOpen() { return open; }
	bool isStandard() { return standard; }
	bool isSame() { return same; }
	bool isWall() { return wall; }
	bool isPlus() { return plus; }
	bool isCascade() { return cascade; }
};
