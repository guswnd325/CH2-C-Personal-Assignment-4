#include <iostream>
#include <vector>
#include <string>
#include <map>
#define MAX_POTION_COUNT 3

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경

    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
};

class StockManager
{
private:
    std::map<std::string, int> stocks;

public:
    void InitStock(const std::string & name)
    {
        stocks[name] = MAX_POTION_COUNT;
    }

    int GetStock(const std::string & name)
    {
        return stocks[name];
    }

    void DispensePotion(const std::string & name)
    {
        if (stocks.find(name) == stocks.end()) {
            std::cout << ">> 등록되지 않은 물약입니다." << std::endl;
            return;
        }

        if (stocks[name] <= 0)
        {
            std::cout << "포션의 재고가 없습니다." << std::endl;
            return;
        }

        stocks[name]--;
        std::cout << "모험가에게 물약을 제공했습니다." << std::endl;
        std::cout << "- 물약 이름: " << name << std::endl;
        std::cout << "  > 재고 : " << stocks[name] << std::endl;
    }

    void ReturnPotion(const std::string& name)
    {
        if (stocks.find(name) == stocks.end()) {
            std::cout << ">> 등록되지 않은 물약입니다." << std::endl;
            return;
        }


        if (stocks[name] >= MAX_POTION_COUNT)
        {
            std::cout << "포션 창고가 꽉 찼습니다." << std::endl;
            return;
        }
        stocks[name]++;
        std::cout << "모험가에게 물약을 돌려받았습니다." << std::endl;
        std::cout << "- 물약 이름: " << name << std::endl;
        std::cout << "  > 재고 : " << stocks[name] << std::endl;
    }
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    StockManager stockManager;

    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        stockManager.InitStock(name);
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    void SearchRecipeByName(const std::string &name) 
    {
        bool flag = false;
        for (int i = 0; i < recipes.size(); i++)
        {
            if (recipes[i].potionName == name)
            {
                ShowRecipe(i);
                flag = true;
            }
        }
        if (!flag)
        {
            std::cout << ">> 데이터가 존재하지 않습니다." << std::endl;
        }
    }

    PotionRecipe& GetRecipeByName(const std::string& name)
    {
        for (int i = 0; i < recipes.size(); i++)
        {
            if (name == recipes[i].potionName)
            {
                return recipes[i];
            }
        }
    }

    void ShowRecipe(int idx)
    {
        std::cout << "- 물약 이름: " << recipes[idx].potionName << std::endl;
        std::cout << "  > 재고: " << stockManager.GetStock(recipes[idx].potionName) << std::endl;
        std::cout << "  > 필요 재료: ";

        // 재료 목록을 순회하며 출력
        for (size_t j = 0; j < recipes[idx].ingredients.size(); ++j) {
            std::cout << recipes[idx].ingredients[j];
            // 마지막 재료가 아니면 쉼표로 구분
            if (j < recipes[idx].ingredients.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
    }

    bool IsValidIngredients(const std::string& ingredients)
    {
        for (int i = 0; i < recipes.size(); i++)
        {
            for (int j = 0; j < recipes[i].ingredients.size(); j++)
            {
                if (recipes[i].ingredients[j] == ingredients)
                {
                    return true;
                }
            }
        }
        return false;
    }

    void SearchRecipeByIngredients(const std::string& ingredients) {
        if (IsValidIngredients(ingredients))
        {
            std::cout << "'" << ingredients  << "' " << "재료가 포함된 물약은 아래와 같습니다." << std::endl;

        }
        else
        {
            std::cout << "'" << ingredients << "' " << "재료가 포함된 물약은 창고에 존재하지 않습니다." << std::endl;

        }

        for (int i = 0; i < recipes.size(); i++)
        {
            for (int j = 0; j < recipes[i].ingredients.size(); j++)
            {
                if (recipes[i].ingredients[j] == ingredients)
                {

                    ShowRecipe(i);
                }
            }
        }
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes()
    {
        if (recipes.empty()) 
        {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i)
        {
            ShowRecipe(i);
        }
        std::cout << "---------------------------\n";
    }
};

int main() {
    AlchemyWorkshop myWorkshop;

    // Default Potion Init
    myWorkshop.addRecipe("체력물약", { "병", "물", "생명의 샘" });
    myWorkshop.addRecipe("마나물약", { "병", "물", "마법의 샘" });
    system("cls");

    while (true) {
        std::cout << "-- 연금술 공방 관리 시스템 --" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 검색(물약 이름)" << std::endl;
        std::cout << "4. 검색(재료 포함)" << std::endl;
        std::cout << "5. 모험가에게 물약 기부하기" << std::endl;
        std::cout << "6. 모험가에게 물약 반환받기" << std::endl;
        std::cout << "7. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "끝") {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {

            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3)
        {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            myWorkshop.SearchRecipeByName(name);
        }
        else if (choice == 4)
        {
            std::string name;
            std::cout << "재료 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            myWorkshop.SearchRecipeByIngredients(name);
        }
        else if (choice == 5)
        {
            std::string name;
            std::cout << "제공할 포션 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            myWorkshop.stockManager.DispensePotion(name);
        }
        else if (choice == 6)
        {
            std::string name;
            std::cout << "반환받은 포션 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            myWorkshop.stockManager.ReturnPotion(name);
        }
        else if (choice == 7) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}
