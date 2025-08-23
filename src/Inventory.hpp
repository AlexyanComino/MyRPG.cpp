#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace MyRpg {
    
    typedef enum itemType {
        WEAPON,
        ARMOR,
        POTION,
        QUEST,
        KEY,
        OTHER,
        ALL
    } itemType;
    
    typedef enum armorType {
        HELMET,
        CHESTPLATE,
        BOOTS
    } armorType;
    
    typedef enum rarity {
        COMMON,
        UNCOMMON,
        RARE,
        EPIC,
        LEGENDARY,
    } rarity;

    class Item {
    public:
        Item(const std::string& name, const std::string& description, 
             itemType type, rarity rarity = COMMON);
        virtual ~Item() = default;

        const std::string& getName() const { return _name; }
        const std::string& getDescription() const { return _description; }
        itemType getType() const { return _type; }
        rarity getRarity() const { return _rarity; }
        sf::Sprite& getSprite() { return _sprite; }
        const sf::Sprite& getSprite() const { return _sprite; }
        
        void setTexture(const std::string& texturePath);

    protected:
        std::string _name;
        std::string _description;
        itemType _type;
        rarity _rarity;
        sf::Texture _texture;
        sf::Sprite _sprite;
    };

    class Weapon : public Item {
    public:
        Weapon(const std::string& name, const std::string& description,
               int damage, float attackSpeed = 1.0f);
        ~Weapon() = default;

        int getDamage() const { return _damage; }
        float getAttackSpeed() const { return _attackSpeed; }

    private:
        int _damage;
        float _attackSpeed;
    };

    class Armor : public Item {
    public:
        Armor(const std::string& name, const std::string& description,
              armorType armorType, int defense, int speedModifier = 0);
        ~Armor() = default;

        armorType getArmorType() const { return _armorType; }
        int getDefense() const { return _defense; }
        int getSpeedModifier() const { return _speedModifier; }

    private:
        armorType _armorType;
        int _defense;
        int _speedModifier;
    };

    class Potion : public Item {
    public:
        Potion(const std::string& name, const std::string& description,
               int healAmount);
        ~Potion() = default;

        int getHealAmount() const { return _healAmount; }
        void use(); // Apply potion effect

    private:
        int _healAmount;
    };

    class InventorySlot {
    public:
        InventorySlot();
        ~InventorySlot() = default;

        bool isEmpty() const { return _item == nullptr; }
        bool isHighlighted() const { return _highlighted; }
        bool isSelected() const { return _selected; }
        
        void setItem(std::unique_ptr<Item> item);
        std::unique_ptr<Item> takeItem(); // Remove and return item
        Item* getItem() const { return _item.get(); }
        
        void setPosition(sf::Vector2f position);
        void setHighlighted(bool highlighted) { _highlighted = highlighted; }
        void setSelected(bool selected) { _selected = selected; }
        
        void update(sf::Vector2f mousePos, bool clicked);
        void display(sf::RenderWindow& window);

    private:
        std::unique_ptr<Item> _item;
        sf::RectangleShape _background;
        sf::RectangleShape _highlight;
        sf::Vector2f _position;
        sf::Vector2f _size;
        bool _highlighted;
        bool _selected;
        
        void updateColors();
    };

    class Inventory {
    public:
        static const int INVENTORY_ROWS = 6;
        static const int INVENTORY_COLS = 8;
        static const int TOTAL_SLOTS = INVENTORY_ROWS * INVENTORY_COLS;

        Inventory();
        ~Inventory() = default;

        bool addItem(std::unique_ptr<Item> item);
        std::unique_ptr<Item> removeItem(int slotIndex);
        
        void addGold(int amount) { _gold += amount; }
        bool removeGold(int amount);
        int getGold() const { return _gold; }
        
        InventorySlot& getSlot(int index) { return *_slots[index]; }
        const InventorySlot& getSlot(int index) const { return *_slots[index]; }
        
        bool isOpen() const { return _isOpen; }
        void open() { _isOpen = true; }
        void close() { _isOpen = false; }
        void toggle() { _isOpen = !_isOpen; }
        
        void update(sf::Vector2f mousePos, bool clicked);
        void display(sf::RenderWindow& window);
        
        // Find item by name or type
        Item* findItem(const std::string& name) const;
        std::vector<Item*> findItemsByType(itemType type) const;

    private:
        std::vector<std::unique_ptr<InventorySlot>> _slots;
        bool _isOpen;
        int _gold;
        
        // UI Elements
        sf::RectangleShape _background;
        sf::Text _titleText;
        sf::Text _goldText;
        sf::Font _font;
        
        // Selected item for description
        Item* _selectedItem;
        sf::RectangleShape _descriptionBackground;
        sf::Text _descriptionText;
        
        void initializeUI();
        void updateGoldDisplay();
        void updateDescription();
        int findEmptySlot() const;
    };

    class PlayerStatus {
    public:
        PlayerStatus();
        ~PlayerStatus() = default;

        // Equipment slots
        void equipWeapon(std::unique_ptr<Weapon> weapon);
        void equipArmor(std::unique_ptr<Armor> armor);
        void unequipWeapon();
        void unequipArmor(armorType type);
        
        Weapon* getEquippedWeapon() const { return _equippedWeapon.get(); }
        Armor* getEquippedArmor(armorType type) const;
        
        // Stats calculation including equipment bonuses
        int getTotalAttack() const;
        int getTotalDefense() const;
        float getTotalSpeed() const;
        
        void display(sf::RenderWindow& window);

    private:
        std::unique_ptr<Weapon> _equippedWeapon;
        std::unique_ptr<Armor> _equippedHelmet;
        std::unique_ptr<Armor> _equippedChestplate;
        std::unique_ptr<Armor> _equippedBoots;
        
        // UI elements for equipment display
        sf::RectangleShape _weaponSlot;
        sf::RectangleShape _helmetSlot;
        sf::RectangleShape _chestplateSlot;
        sf::RectangleShape _bootsSlot;
        
        void initializeSlots();
    };
}

#endif /* !INVENTORY_HPP_ */