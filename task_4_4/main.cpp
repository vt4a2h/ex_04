#include <iostream>
#include <cstring>
#include <vector>

namespace dnd {

    class Item {};
    using InventorySize = size_t;
    using ItemId        = std::string;
    using ItemsIds      = std::vector<ItemId>;

    class Inventory
    {
    public:
        Inventory(InventorySize size);
        Inventory(const Inventory &src);
        ~Inventory();

        Inventory &operator =(const Inventory &rhs);

        Item takeItem(ItemId id) const;
        void putItem(const Item& item);
        void removeItem(ItemId id);
        bool contains(ItemId id) const;

        bool any() const;
        InventorySize itemsCount() const;
        ItemsIds      ids()        const;
        InventorySize freeSpace()  const;
    };

} // namespace dnd

int main()
{
    return 0;
}

