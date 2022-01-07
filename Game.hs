data Item = Sword | Bow | MagicWand
    deriving (Eq)

instance Show Item where
    show = showItem

data Mob = Skeleton (Maybe Item) | Witch (Maybe Item) | Mummy
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
createArcher = Skeleton (Just Bow)

createKnight :: Mob -- a Skeleton holding a Sword
createKnight = Skeleton (Just Sword)

createWitch :: Mob -- a Which holding Nothing
createWitch = Witch Nothing

createSorceress :: Mob -- a Which holding a MagicWand
createSorceress = Witch (Just MagicWand)

showMob :: Mob -> String
showMob Mummy = "mummy"
showMob (Skeleton (Just Bow)) = "doomed archer"
showMob (Skeleton (Just Sword)) = "dead knight"
showMob (Skeleton (Just MagicWand)) = "skeleton holding a " ++ showItem MagicWand
showMob (Witch Nothing) = "witch"
showMob (Witch (Just MagicWand)) = "sorceress"
showMob (Witch (Just Sword)) = "witch holding a Sword"
showMob _ = ""

create :: String -> Maybe Mob
create "mummy" = Just Mummy
create "doomed archer" = Just $ Skeleton (Just Bow)
create "dead knight" = Just $ Skeleton (Just Sword)
create "witch" = Just $ Witch Nothing 
create "sorceress" = Just $ Witch (Just MagicWand)
create _ = Nothing

equip :: Item -> Mob -> Maybe Mob
equip a Mummy = Just Mummy
equip a (Skeleton (Just _))= Just $ Skeleton (Just a)
equip a (Witch (Just _)) = Just $ Witch (Just a)
equip a _ = Nothing
