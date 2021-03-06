data Item = Sword | Bow | MagicWand
    deriving (Eq)

instance Show Item where
    show = showItem

data Mob = Skeleton Item | Witch (Maybe Item) | Mummy
    deriving (Eq)

instance Show Mob where
    show = showMob

showItem :: Item -> String
showItem Sword = "sword"
showItem Bow = "bow"
showItem MagicWand = "magic wand"


createMummy :: Mob -- a Mummy
createMummy = Mummy

createArcher :: Mob -- a Skeleton holding a Bow
createArcher = Skeleton Bow

createKnight :: Mob -- a Skeleton holding a Sword
createKnight = Skeleton Sword

createWitch :: Mob -- a Which holding Nothing
createWitch = Witch Nothing

createSorceress :: Mob -- a Which holding a MagicWand
createSorceress = Witch (Just MagicWand)

showMob :: Mob -> String
showMob Mummy = "mummy"
showMob (Skeleton Bow) = "doomed archer"
showMob (Skeleton Sword) = "dead knight"
showMob (Skeleton MagicWand) = "skeleton holding a " ++ showItem MagicWand
showMob (Witch Nothing) = "witch"
showMob (Witch (Just MagicWand)) = "sorceress"
showMob (Witch (Just x)) = "witch holding a " ++ showItem x
--showMob _ = ""

create :: String -> Maybe Mob
create "mummy" = Just Mummy
create "doomed archer" = Just $ Skeleton Bow
create "dead knight" = Just $ Skeleton Sword
create "witch" = Just $ Witch Nothing 
create "sorceress" = Just $ Witch (Just MagicWand)
create _ = Nothing

equip :: Item -> Mob -> Maybe Mob
equip a Mummy = Just Mummy
equip a (Skeleton b)= Just $ Skeleton a
equip a (Witch (Just b)) = Just $ Witch (Just a)
equip a _ = Just $ Witch (Just a)

class HasItem a where
    getItem :: a -> Maybe Item;
    hasItem :: a -> Bool;
    hasItem a = case getItem a of
        Nothing -> False
        (Just _) -> True

instance HasItem Mob where
    getItem Mummy = Nothing
    getItem (Witch (Just x)) = Just x
    getItem (Skeleton x) = Just x
    getItem _ = Nothing