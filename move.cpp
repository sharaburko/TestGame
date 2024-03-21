#include "move.h"

std::vector <std::vector <int>> movesActivChip(int &activChip, std::vector <std::vector <int>> & arr) {
    std::vector <int> temp;
    std::vector <std::vector <int>> cPoints;

    for (size_t i = 0; i < arr.size(); i++) {

        if (*arr[i].begin() == activChip) {
            temp.push_back(activChip);
            temp.push_back(*(arr[i].end() - 1));
            cPoints.push_back(temp);
            temp.clear();
        }
        else if (*(arr[i].end() - 1) == activChip) {
            temp.push_back(activChip);
            temp.push_back(*arr[i].begin());
            cPoints.push_back(temp);
            temp.clear();
        }
    }

    for (size_t i = 0; i < cPoints.size(); i++) {

        for (size_t j = 0; j < arr.size(); j++) {

            if (*arr[j].begin() == *(cPoints[i].end() - 1)) {

                if (find(cPoints[i].begin(), cPoints[i].end(), *(arr[j].end() - 1)) == cPoints[i].end()) {
                    temp = cPoints[i];
                    temp.push_back(*(arr[j].end() - 1));
                    cPoints.push_back(temp);
                    temp.clear();
                }

            }
            else if (*(arr[j].end() - 1) == *(cPoints[i].end() - 1)) {

                if (find(cPoints[i].begin(), cPoints[i].end(), *(arr[j].begin())) == cPoints[i].end()) {
                        temp = cPoints[i];
                        temp.push_back(*(arr[j].begin()));
                        cPoints.push_back(temp);
                        temp.clear();
                }

            }
        }

    }

    return cPoints;
}

