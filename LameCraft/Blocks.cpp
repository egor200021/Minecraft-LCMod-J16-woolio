#include "Blocks.h"



GrassBlock::GrassBlock():BaseBlock()
{
	textureRow = 0;

	upPlane = 0;
	downPlane = 2;
	sidePlane = 3;
	editable = true;
	transparent = false;
	soundType = 0;

	loot = 2;
	material = 3;

}

block_t GrassBlock::getID(){ return 1;}

DirtBlock::DirtBlock():BaseBlock()
{
	textureRow = 0;

	upPlane = 2;
	downPlane = 2;
	sidePlane = 2;
	editable = true;
	transparent = false;
	soundType = 1;

	loot = 2;
	material = 3;

}

block_t DirtBlock::getID(){ return 2;}


RockBlock::RockBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = false;
	soundType = 2;

	loot = 36;
	material = 2;

}

block_t RockBlock::getID(){ return 3;}


WaterBlock::WaterBlock():BaseBlock()
{
	textureRow = 3;

    upPlane = 2;
    downPlane = 2;
    sidePlane = 2;
	editable = false;
	transparent = true;
	soundType = -1;

	loot = 4;

}

block_t WaterBlock::getID(){ return 4;}

GoldBlock::GoldBlock():BaseBlock()
{
	textureRow = 6;

	upPlane = 2;
	downPlane = 2;
	sidePlane = 2;
	editable = true;
	transparent = false;
	soundType = 2;

	loot = 5;
	material = 2;

}

block_t GoldBlock::getID(){ return 5;}

LadderBlock::LadderBlock():BaseBlock()
{
	textureRow = 3;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = true;
	soundType = 3;

	loot = 6;
	material = 1;

}
block_t LadderBlock::getID(){ return 6;}


SandBlock::SandBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 2;
	downPlane = 2;
	sidePlane = 2;
	editable = true;
	transparent = false;
	soundType = 1;

	loot = 7;
	material = 3;

}
block_t SandBlock::getID(){ return 7;}


WoodBlock::WoodBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 2;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 8;
	material = 1;

}
block_t WoodBlock::getID(){ return 8;}

LeavesBlock::LeavesBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 3;
	downPlane = 3;
	sidePlane = 3;
	editable = true;
	transparent = false;
	soundType = 0;

	loot = 9;
	material = 4;

}
block_t LeavesBlock::getID(){ return 9;}


GrayWoolBlock::GrayWoolBlock():BaseBlock()
{
	textureRow = 4;

	upPlane = 3;
	downPlane = 3;
	sidePlane = 3;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 10;
	material = 4;

}
block_t GrayWoolBlock::getID(){ return 10;}


BlackWoolBlock::BlackWoolBlock():BaseBlock()
{
	textureRow = 3;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 11;

}
block_t BlackWoolBlock::getID(){ return 11;}


RedWoolBlock::RedWoolBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 4;
	downPlane = 4;
	sidePlane = 4;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 12;

}
block_t RedWoolBlock::getID(){ return 12;}


DarkGreyWoolBlock::DarkGreyWoolBlock():BaseBlock()
{
	textureRow = 4;

	upPlane = 5;
	downPlane = 5;
	sidePlane = 5;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 13;

}
block_t DarkGreyWoolBlock::getID(){ return 13;}



BrownWoolBlock::BrownWoolBlock():BaseBlock()
{
	textureRow = 5;

	upPlane = 5;
	downPlane = 5;
	sidePlane = 5;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 14;

}
block_t BrownWoolBlock::getID(){ return 14;}


LightBlackWoolBlock::LightBlackWoolBlock():BaseBlock()
{
	textureRow = 3;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 15;

}
block_t LightBlackWoolBlock::getID(){ return 15;}



PinkWoolBlock::PinkWoolBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 5;
	downPlane = 5;
	sidePlane = 5;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 16;

}
block_t PinkWoolBlock::getID(){ return 16;}


LightGreenWoolBlock::LightGreenWoolBlock():BaseBlock()
{
	textureRow = 4;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 17;

}
block_t LightGreenWoolBlock::getID(){ return 17;}

YellowWoolBlock::YellowWoolBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 3;
	downPlane = 3;
	sidePlane = 3;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 18;

}
block_t YellowWoolBlock::getID(){ return 18;}

BlueWoolBlock::BlueWoolBlock():BaseBlock()
{
	textureRow = 0;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 19;

}
block_t BlueWoolBlock::getID(){ return 19;}

LightBlueWoolBlock::LightBlueWoolBlock():BaseBlock()
{
	textureRow = 0;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 20;

}
block_t LightBlueWoolBlock::getID(){ return 20;}

FioletWoolBlock::FioletWoolBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 3;
	loot = 21;

}
block_t FioletWoolBlock::getID(){ return 21;}

PastelWoolBlock::PastelWoolBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 22;

}
block_t PastelWoolBlock::getID(){ return 22;}

LightFioletWoolBlock::LightFioletWoolBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;
	soundType = 3;


	loot = 23;

}
block_t LightFioletWoolBlock::getID(){ return 23;}

OrangeWoolBlock::OrangeWoolBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 24;

}
block_t OrangeWoolBlock::getID(){ return 24;}

CactusBlock::CactusBlock():BaseBlock()
{
	textureRow = 5;

	upPlane = 0;
	downPlane = 2;
	sidePlane = 1;
	editable = true;
	transparent = true;
    blockSpecial = true;
	soundType = 3;

	loot = 25;
	material = 1;

}
block_t CactusBlock::getID(){ return 25;}

AllSnowBlock::AllSnowBlock():BaseBlock()
{
	textureRow = 0;

	upPlane = 4;
	downPlane = 4;
	sidePlane = 4;
	editable = true;
	transparent = false;
	soundType = 0;

	loot = 26;

}
block_t AllSnowBlock::getID(){ return 26;}

BrickBlock::BrickBlock():BaseBlock()
{
	textureRow = 4;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;

	loot = 27;
	material = 2;

}
block_t BrickBlock::getID(){ return 27;}

CageBlock::CageBlock():BaseBlock()
{
	textureRow = 6;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 1;
	editable = true;
	transparent = true;
	soundType = 2;

	loot = 28;
	material = 2;

}
block_t CageBlock::getID(){ return 28;}

SnowBlock::SnowBlock():BaseBlock()
{
	textureRow = 0;

	upPlane = 4;
	downPlane = 2;
	sidePlane = 5;
	editable = true;
	transparent = false;
	soundType = 0;

	loot = 29;
	material = 3;

}
block_t SnowBlock::getID(){ return 29;}

DarkWoodBlock::DarkWoodBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 5;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 30;
	material = 1;

}
block_t DarkWoodBlock::getID(){ return 30;}

WhiteWoodBlock::WhiteWoodBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 4;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 31;
	material = 1;

}
block_t WhiteWoodBlock::getID(){ return 31;}

IceBlock::IceBlock():BaseBlock()
{
	textureRow = 6;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = true;
	soundType = 2;

	loot = -1;

}
block_t IceBlock::getID(){ return 32;}

CaneBlock::CaneBlock():BaseBlock()
{
	textureRow = 5;

	upPlane = 4;
	downPlane = 4;
	sidePlane = 3;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 33;

}
block_t CaneBlock::getID(){ return 33;}

BoxBlock::BoxBlock():BaseBlock() // planks
{
	textureRow = 4;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = false;
	soundType = 3;

    loot = 34;
    material = 1;

}
block_t BoxBlock::getID(){ return 34;}

ShelfBlock::ShelfBlock():BaseBlock()
{
	textureRow = 4;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 1;
	editable = true;
	transparent = false;
	soundType = 3;

    loot = 35;

}
block_t ShelfBlock::getID(){ return 35;}

CobbleStone::CobbleStone():BaseBlock()
{
	textureRow = 4;

	upPlane = 2;
	downPlane = 2;
	sidePlane = 2;
	editable = true;
	transparent = false;
	soundType = 2;

		loot = 36;

}
block_t CobbleStone::getID(){ return 36;}

DrySandBlock::DrySandBlock():BaseBlock()
{
	textureRow = 4;

	upPlane = 8;
	downPlane = 8;
	sidePlane = 8;
	editable = true;
	transparent = false;
	soundType = 1;

		loot = 36;

}
block_t DrySandBlock::getID(){ return 37;}

SnowLewesBlock::SnowLewesBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = false;
	soundType = 0;

		loot = 37;

}
block_t SnowLewesBlock::getID(){ return 38;}

Sponge::Sponge():BaseBlock()
{
	textureRow = 3;

	upPlane = 10;
	downPlane = 10;
	sidePlane = 10;
	editable = true;
	transparent = false;
	soundType = 1;

		loot = 38;

}
block_t Sponge::getID(){ return 39;}

GlassBlock::GlassBlock():BaseBlock()
{
	textureRow = 3;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 1;
	editable = true;
	transparent = true;
	soundType = 2;

		loot = -1;

}
block_t GlassBlock::getID(){ return 40;}

IronOre::IronOre():BaseBlock()
{
	textureRow = 6;

	upPlane = 3;
	downPlane = 3;
	sidePlane = 3;
	editable = true;
	transparent = false;
	soundType = 2;

		loot = 41;
		material = 2;

}
block_t IronOre::getID(){ return 41;}

CoalOre::CoalOre():BaseBlock()
{
	textureRow = 6;

	upPlane = 4;
	downPlane = 4;
	sidePlane = 4;
	editable = true;
	transparent = false;
	soundType = 2;

	loot = 277;
	material = 2;

}
block_t CoalOre::getID(){ return 42;}

DiamondOre::DiamondOre():BaseBlock()
{
	textureRow = 6;

	upPlane = 5;
	downPlane = 5;
	sidePlane = 5;
	editable = true;
	transparent = false;
	soundType = 2;

	loot = 279;
	material = 2;

}
block_t DiamondOre::getID(){ return 43;}

RedstoneOre::RedstoneOre():BaseBlock()
{
	textureRow = 6;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 2;

	loot = 44;
	material = 2;

}
block_t RedstoneOre::getID(){ return 44;}

SlamRockBlock::SlamRockBlock():BaseBlock()
{
	textureRow = 6;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;
	soundType = 2;

	material = 2;

}
block_t SlamRockBlock::getID(){ return 45;}

WaterRockBlock::WaterRockBlock():BaseBlock()
{
	textureRow = 5;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 2;

}
block_t WaterRockBlock::getID(){ return 46;}

JackOLantern::JackOLantern():BaseBlock()
{
	textureRow = 7;

	upPlane = 0;
	downPlane = 1;
	sidePlane = 2;
	editable = true;
	transparent = false;
	soundType = 2;
	lightSource = true;

}
block_t JackOLantern::getID(){ return 47;}

Torch::Torch():BaseBlock()
{
	textureRow = 7;

	upPlane = 3;
	downPlane = 3;
	sidePlane = 3;
	editable = true;
	transparent = false;
	soundType = 2;
	lightSource = true;
	blockSpecial = true;

		loot = 48;

}
block_t Torch::getID(){ return 48;}

Door1::Door1():BaseBlock()
{
	textureRow = 3;

	upPlane = 11;
	downPlane = 11;
	sidePlane = 9;
	editable = true;
	transparent = true;
	blockSpecial = true;

}
block_t Door1::getID(){ return 49;}

Door2::Door2():BaseBlock()
{
	textureRow = 4;

	upPlane = 9;
	downPlane = 9;
	sidePlane = 9;
	editable = true;
	transparent = true;
	blockSpecial = true;

}
block_t Door2::getID(){ return 50;}

HalfBlocks::HalfBlocks():BaseBlock()
{
	textureRow = 1;

	upPlane = 8;
	downPlane = 8;
	sidePlane = 9;
	editable = true;
	transparent = false;

}
block_t HalfBlocks::getID(){ return 51;}

SandStone1::SandStone1():BaseBlock()
{
	textureRow = 7;

	upPlane = 4;
	downPlane = 5;
	sidePlane = 6;
	editable = true;
	transparent = false;

}
block_t SandStone1::getID(){ return 52;}

SandStone2::SandStone2():BaseBlock()
{
	textureRow = 7;

	upPlane = 4;
	downPlane = 4;
	sidePlane = 4;
	editable = true;
	transparent = false;

}
block_t SandStone2::getID(){ return 53;}

SandStone3::SandStone3():BaseBlock()
{
	textureRow = 7;

	upPlane = 5;
	downPlane = 5;
	sidePlane = 5;
	editable = true;
	transparent = false;

}
block_t SandStone3::getID(){ return 54;}

StoneBrick1::StoneBrick1():BaseBlock()
{
	textureRow = 4;

	upPlane = 4;
	downPlane = 4;
	sidePlane = 4;
	editable = true;
	transparent = false;

}
block_t StoneBrick1::getID(){ return 55;}

StoneBrick2::StoneBrick2():BaseBlock()
{
	textureRow = 3;

	upPlane = 3;
	downPlane = 3;
	sidePlane = 3;
	editable = true;
	transparent = false;

}
block_t StoneBrick2::getID(){ return 56;}

StoneBrick3::StoneBrick3():BaseBlock()
{
	textureRow = 3;

	upPlane = 4;
	downPlane = 4;
	sidePlane = 4;
	editable = true;
	transparent = false;

}
block_t StoneBrick3::getID(){ return 57;}

StoneBrick4::StoneBrick4():BaseBlock()
{
	textureRow = 3;

	upPlane = 5;
	downPlane = 5;
	sidePlane = 5;
	editable = true;
	transparent = false;

}
block_t StoneBrick4::getID(){ return 58;}

JungleWood::JungleWood():BaseBlock()
{
	textureRow = 2;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 8;
	editable = true;
	transparent = false;

}
block_t JungleWood::getID(){ return 59;}

Planks1::Planks1():BaseBlock()
{
	textureRow = 5;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;

		loot = 60;
		material = 1;

}
block_t Planks1::getID(){ return 60;}

Planks2::Planks2():BaseBlock()
{
	textureRow = 5;

	upPlane = 8;
	downPlane = 8;
	sidePlane = 8;
	editable = true;
	transparent = false;

		loot = 61;

}
block_t Planks2::getID(){ return 61;}

Planks3::Planks3():BaseBlock()
{
	textureRow = 6;

	upPlane = 8;
	downPlane = 8;
	sidePlane = 8;
	editable = true;
	transparent = false;

		loot = 62;

}
block_t Planks3::getID(){ return 62;}

Mycelium::Mycelium():BaseBlock()
{
	textureRow = 0;

	upPlane = 8;
	downPlane = 2;
	sidePlane = 9;
	editable = true;
	transparent = false;

}
block_t Mycelium::getID(){ return 63;}

Diamond::Diamond():BaseBlock()
{
	textureRow = 8;

	upPlane = 2;
	downPlane = 2;
	sidePlane = 2;
	editable = true;
	transparent = false;

		loot = 64;
		material = 2;

}
block_t Diamond::getID(){ return 64;}

Gold::Gold():BaseBlock()
{
	textureRow = 8;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 1;
	editable = true;
	transparent = false;

		loot = 65;
		material = 2;

}
block_t Gold::getID(){ return 65;}


Iron::Iron():BaseBlock()
{
	textureRow = 8;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = false;

		loot = 66;
		material = 2;

}
block_t Iron::getID(){ return 66;}

NetherBrick::NetherBrick():BaseBlock()
{
    textureRow = 0;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 1;
    editable = true;
    transparent = false;

}
block_t NetherBrick::getID(){ return 67;}

Netherrack::Netherrack():BaseBlock()
{
    textureRow = 2;

    upPlane = 9;
    downPlane = 9;
    sidePlane = 9;
    editable = true;
    transparent = false;

}
block_t Netherrack::getID(){ return 68;}

SoulSand::SoulSand():BaseBlock()
{
    textureRow = 2;

    upPlane = 10;
    downPlane = 10;
    sidePlane = 10;
    editable = true;
    transparent = false;

}
block_t SoulSand::getID(){ return 69;}

Grass::Grass():BaseBlock()
{
    textureRow = 5;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 9;
    editable = true;
    transparent = true;

}
block_t Grass::getID(){ return 70;}

MelonBlock::MelonBlock():BaseBlock()
{
    textureRow = 8;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 3;
    editable = true;
    transparent = false;

    	loot = 71;

}
block_t MelonBlock::getID(){ return 71;}

JukeBox::JukeBox():BaseBlock()
{
    textureRow = 8;

    upPlane = 6;
    downPlane = 5;
    sidePlane = 5;
    editable = true;
    transparent = false;

}
block_t JukeBox::getID(){ return 72;}


EndStone::EndStone():BaseBlock()
{
    textureRow = 0;

    upPlane = 10;
    downPlane = 10;
    sidePlane = 10;
    editable = true;
    transparent = false;

}
block_t EndStone::getID(){ return 73;}

Pumpkin::Pumpkin():BaseBlock()
{
    textureRow = 9;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 0;
    sidePlane2 = 12;
    sidePlane3 = 12;
    sidePlane4 = 12;
    editable = true;
    transparent = false;
    blockSpecial = true;

    	loot = 74;
    	material = 1;

}
block_t Pumpkin::getID(){ return 74;}

GlowStone::GlowStone():BaseBlock()
{
    textureRow = 3;

    upPlane = 8;
    downPlane = 8;
    sidePlane = 8;
    editable = true;
    transparent = true;
    lightSource = true;

}
block_t GlowStone::getID(){ return 75;}

Basalt::Basalt():BaseBlock()
{
    textureRow = 9;

    upPlane = 2;
    downPlane = 2;
    sidePlane = 2;
    editable = true;
    transparent = false;

    loot =  101;
    material = 2;

}
block_t Basalt::getID(){ return 76;}

Gabbro::Gabbro():BaseBlock()
{
    textureRow = 9;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 4;
    editable = true;
    transparent = false;

    loot = 102;
    material = 2;

}
block_t Gabbro::getID(){ return 77;}

Dacite::Dacite():BaseBlock()
{
    textureRow = 9;

    upPlane = 6;
    downPlane = 6;
    sidePlane = 6;
    editable = true;
    transparent = false;

    loot = 103;
    material = 2;

}
block_t Dacite::getID(){ return 78;}

Soil::Soil():BaseBlock()
{
    textureRow = 9;

    upPlane = 13;
    downPlane = 13;
    sidePlane = 13;
    editable = true;
    transparent = false;

    loot = 2;
    material = 3;

}
block_t Soil::getID(){ return 79;}

MooshroomLeaves::MooshroomLeaves():BaseBlock()
{
    textureRow = 8;

    upPlane = 9;
    downPlane = 8;
    sidePlane = 9;
    editable = true;
    transparent = false;

}
block_t MooshroomLeaves::getID(){ return 80;}

MooshroomWood::MooshroomWood():BaseBlock()
{
    textureRow = 8;

    upPlane = 8;
    downPlane = 8;
    sidePlane = 7;
    editable = true;
    transparent = false;

}
block_t MooshroomWood::getID(){ return 81;}

HalfBlock8::HalfBlock8():BaseBlock()
{
    textureRow = 4;

    upPlane = 2;
    downPlane = 2;
    sidePlane = 2;
    editable = true;
    transparent = false;
    blockSpecial = true;

}
block_t HalfBlock8::getID(){ return 82;}

HalfBlock0::HalfBlock0():BaseBlock()
{
    textureRow = 4;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 4;
    editable = true;
    transparent = false;
    blockSpecial = true;

}
block_t HalfBlock0::getID(){ return 83;}

HalfBlock1::HalfBlock1():BaseBlock()
{
    textureRow = 1;

    upPlane = 8;
    downPlane = 8;
    sidePlane = 9;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

}
block_t HalfBlock1::getID(){ return 84;}

HalfBlock2::HalfBlock2():BaseBlock()
{
    textureRow = 7;

    upPlane = 4;
    downPlane = 5;
    sidePlane = 4;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

}
block_t HalfBlock2::getID(){ return 85;}

HalfBlock3::HalfBlock3():BaseBlock()
{
    textureRow = 4;

    upPlane = 0;
    downPlane = 0;
    sidePlane = 0;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

}
block_t HalfBlock3::getID(){ return 86;}

HalfBlock4::HalfBlock4():BaseBlock()
{
    textureRow = 5;

    upPlane = 7;
    downPlane = 7;
    sidePlane = 7;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

}
block_t HalfBlock4::getID(){ return 87;}

HalfBlock5::HalfBlock5():BaseBlock()
{
    textureRow = 5;

    upPlane = 8;
    downPlane = 8;
    sidePlane = 8;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

}
block_t HalfBlock5::getID(){ return 88;}

HalfBlock6::HalfBlock6():BaseBlock()
{
    textureRow = 6;

    upPlane = 8;
    downPlane = 8;
    sidePlane = 8;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

}
block_t HalfBlock6::getID(){ return 89;}

HalfBlock7::HalfBlock7():BaseBlock()
{
    textureRow = 6;

    upPlane = 9;
    downPlane = 9;
    sidePlane = 9;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

}
block_t HalfBlock7::getID(){ return 90;}

Cake::Cake():BaseBlock()
{
    textureRow = 0;

    upPlane = 11;
    downPlane = 12;
    sidePlane = 13;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

}
block_t Cake::getID(){ return 91;}

TrapDoor::TrapDoor():BaseBlock()
{
    textureRow = 8;

    upPlane = 11;
    downPlane = 11;
    sidePlane = 11;
    editable = true;
    transparent = true;
    blockSpecial = true;
    lightSource = false;

}
block_t TrapDoor::getID(){ return 92;}

Snow2::Snow2():BaseBlock()
{
    textureRow = 0;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 4;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

}
block_t Snow2::getID(){ return 93;}

Table::Table():BaseBlock()
{
    textureRow = 9;

    upPlane = 10;
    downPlane = 8;
    sidePlane = 9;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

}
block_t Table::getID(){ return 94;}

AetherStone::AetherStone():BaseBlock()
{
    textureRow = 9;

    upPlane = 11;
    downPlane = 11;
    sidePlane = 11;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t AetherStone::getID(){ return 95;}

MushRoomLeave::MushRoomLeave():BaseBlock()
{
    textureRow = 8;

    upPlane = 10;
    downPlane = 8;
    sidePlane = 10;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t MushRoomLeave::getID(){ return 96;}

MossAetherStone::MossAetherStone():BaseBlock()
{
    textureRow = 10;

    upPlane = 0;
    downPlane = 0;
    sidePlane = 0;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t MossAetherStone::getID(){ return 97;}

AetherBlock1::AetherBlock1():BaseBlock()
{
    textureRow = 10;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 1;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t AetherBlock1::getID(){ return 98;}

ClayBlock::ClayBlock():BaseBlock()
{
    textureRow = 1;

    upPlane = 10;
    downPlane = 10;
    sidePlane = 10;
    editable = true;
    transparent = false;
    lightSource = false;

    loot = 99;
    material = 3;

}
block_t ClayBlock::getID(){ return 99;}

Chest::Chest():BaseBlock()
{
    textureRow = 10;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 3;
    sidePlane2 = 5;
    sidePlane3 = 5;
    sidePlane4 = 5;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 100;
    material = 1;

}
block_t Chest::getID(){ return 100;}

BasaltCobble::BasaltCobble():BaseBlock()
{
    textureRow = 9;

    upPlane = 3;
    downPlane = 3;
    sidePlane = 3;
    editable = true;
    transparent = false;
    lightSource = false;

    loot = 101;
    material = 2;

}
block_t BasaltCobble::getID(){ return 101;}

GabbroCobble::GabbroCobble():BaseBlock()
{
    textureRow = 9;

    upPlane = 5;
    downPlane = 5;
    sidePlane = 5;
    editable = true;
    transparent = false;
    lightSource = false;

    loot = 102;
    material = 2;

}
block_t GabbroCobble::getID(){ return 102;}

DaciteCobble::DaciteCobble():BaseBlock()
{
    textureRow = 9;

    upPlane = 7;
    downPlane = 7;
    sidePlane = 7;
    editable = true;
    transparent = false;
    lightSource = false;

    loot = 103;
    material = 2;

}
block_t DaciteCobble::getID(){ return 103;}

Furnace::Furnace():BaseBlock()
{
    textureRow = 10;

    upPlane = 12;
    downPlane = 12;
    sidePlane = 8;
    editable = true;
    transparent = false;
    lightSource = false;

    loot = 104;
    material = 2;

}
block_t Furnace::getID(){ return 104;}

Crafting::Crafting():BaseBlock()
{
    textureRow = 10;

    upPlane = 10;
    downPlane = 10;
    sidePlane = 11;
    editable = true;
    transparent = false;
    lightSource = false;

    loot = 105;
    material = 1;

}
block_t Crafting::getID(){ return 105;}

JungleLeaves::JungleLeaves():BaseBlock()
{
    textureRow = 7;

    upPlane = 10;
    downPlane = 10;
    sidePlane = 10;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t JungleLeaves::getID(){ return 106;}

Granite::Granite():BaseBlock()
{
    textureRow = 2;

    upPlane = 13;
    downPlane = 13;
    sidePlane = 13;
    editable = true;
    transparent = false;
    lightSource = false;

    loot = 125;
    material = 2;

}
block_t Granite::getID(){ return 107;}

Rhyolite::Rhyolite():BaseBlock()
{
    textureRow = 2;

    upPlane = 12;
    downPlane = 12;
    sidePlane = 12;
    editable = true;
    transparent = false;
    lightSource = false;

    loot = 126;
    material = 2;

}
block_t Rhyolite::getID(){ return 108;}

Komatiite::Komatiite():BaseBlock()
{
    textureRow = 2;

    upPlane = 11;
    downPlane = 11;
    sidePlane = 11;
    editable = true;
    transparent = false;
    lightSource = false;

    loot = 127;
    material = 2;

}
block_t Komatiite::getID(){ return 109;}

TNT::TNT():BaseBlock()
{
    textureRow = 1;

    upPlane = 13;
    downPlane = 12;
    sidePlane = 14;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t TNT::getID(){ return 110;}

Nuclear::Nuclear():BaseBlock()
{
    textureRow = 1;

    upPlane = 15;
    downPlane = 15;
    sidePlane = 15;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t Nuclear::getID(){ return 111;}

Lava::Lava():BaseBlock()
{
    textureRow = 11;

    upPlane = 0;
    downPlane = 0;
    sidePlane = 0;
    editable = false;
    transparent = true;
    lightSource = true;

}
block_t Lava::getID(){ return 112;}

Gravel::Gravel():BaseBlock()
{
    textureRow = 11;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 1;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t Gravel::getID(){ return 113;}

LavaStone::LavaStone():BaseBlock()
{
    textureRow = 11;

    upPlane = 2;
    downPlane = 2;
    sidePlane = 2;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t LavaStone::getID(){ return 114;}

LavaObsidian::LavaObsidian():BaseBlock()
{
    textureRow = 11;

    upPlane = 3;
    downPlane = 3;
    sidePlane = 3;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t LavaObsidian::getID(){ return 115;}

BlackStone::BlackStone():BaseBlock()
{
    textureRow = 11;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 4;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t BlackStone::getID(){ return 116;}

CryObsidian::CryObsidian():BaseBlock()
{
    textureRow = 11;

    upPlane = 5;
    downPlane = 5;
    sidePlane = 5;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t CryObsidian::getID(){ return 117;}

MossBlack::MossBlack():BaseBlock()
{
    textureRow = 11;

    upPlane = 6;
    downPlane = 6;
    sidePlane = 6;
    editable = true;
    transparent = false;
    lightSource = false;

}
block_t MossBlack::getID(){ return 118;}

Flower1::Flower1():BaseBlock()
{
    textureRow = 5;

    sidePlane = 10;
    downPlane = 10;
    upPlane = 10;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 119;

}
block_t Flower1::getID(){ return 119;}

Flower2::Flower2():BaseBlock()
{
    textureRow = 5;

    sidePlane = 11;
    downPlane = 11;
    upPlane = 11;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 120;

}
block_t Flower2::getID(){ return 120;}



Sapling::Sapling():BaseBlock()
{
    textureRow = 5;

    upPlane = 14;
    downPlane = 14;
    sidePlane = 14;
    editable = true;
    transparent = true;
    blockSpecial = true;

    loot = 121;

}
block_t Sapling::getID(){ return 121;}

Pumpkin2::Pumpkin2():BaseBlock()
{
    textureRow = 9;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 12;
    sidePlane2 = 0;
    sidePlane3 = 12;
    sidePlane4 = 12;
    editable = true;
    transparent = false;
    blockSpecial = true;


    loot = 74;
}
block_t Pumpkin2::getID(){ return 122;}

Pumpkin3::Pumpkin3():BaseBlock()
{
    textureRow = 9;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 12;
    sidePlane2 = 12;
    sidePlane3 = 0;
    sidePlane4 = 12;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 74;

}
block_t Pumpkin3::getID(){ return 123;}


Pumpkin4::Pumpkin4():BaseBlock()
{
    textureRow = 9;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 12;
    sidePlane2 = 12;
    sidePlane3 = 12;
    sidePlane4 = 0;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 74;

}
block_t Pumpkin4::getID(){ return 124;}

GranitCobble::GranitCobble():BaseBlock()
{
    textureRow = 6;

    upPlane = 13;
    downPlane = 13;
    sidePlane = 13;

    editable = true;
    transparent = false;

    loot = 125;
    material = 2;

}
block_t GranitCobble::getID(){ return 125;}

RhyoliteCobble::RhyoliteCobble():BaseBlock()
{
    textureRow = 6;

    upPlane = 12;
    downPlane = 12;
    sidePlane = 12;
    editable = true;
    transparent = false;

    loot = 126;
    material = 2;

}
block_t RhyoliteCobble::getID(){ return 126;}

KomatiiteCobble::KomatiiteCobble():BaseBlock()
{
    textureRow = 6;

    upPlane = 11;
    downPlane = 11;
    sidePlane = 11;
    editable = true;
    transparent = false;

    loot = 127;
    material = 2;

}
block_t KomatiiteCobble::getID(){ return 127;}

MarbleCobble::MarbleCobble():BaseBlock()
{
    textureRow = 6;

    upPlane = 14;
    downPlane = 14;
    sidePlane = 14;
    editable = true;
    transparent = false;

    loot = 128;
    material = 2;

}
block_t MarbleCobble::getID(){ return 128;}

Marble::Marble():BaseBlock()
{
    textureRow = 9;

    upPlane = 14;
    downPlane = 14;
    sidePlane = 14;
    editable = true;
    transparent = false;

    loot = 128;
    material = 2;

}
block_t Marble::getID(){ return 129;}

Lignite::Lignite():BaseBlock()
{
    textureRow = 2;

    upPlane = 15;
    downPlane = 15;
    sidePlane = 15;
    editable = true;
    transparent = false;

    loot = 282;
    material = 2;

}
block_t Lignite::getID(){ return 130;}

Chest2::Chest2():BaseBlock()
{
    textureRow = 10;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 5;
    sidePlane2 = 3;
    sidePlane3 = 5;
    sidePlane4 = 5;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 100;
    material = 1;


}
block_t Chest2::getID(){ return 131;}

Chest3::Chest3():BaseBlock()
{
    textureRow = 10;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 5;
    sidePlane2 = 5;
    sidePlane3 = 3;
    sidePlane4 = 5;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 100;
    material = 1;


}
block_t Chest3::getID(){ return 132;}

Chest4::Chest4():BaseBlock()
{
    textureRow = 10;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 5;
    sidePlane2 = 5;
    sidePlane3 = 5;
    sidePlane4 = 3;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 100;
    material = 1;


}
block_t Chest4::getID(){ return 133;}


WheatBlock1::WheatBlock1():BaseBlock()
{
    textureRow = 7;

    sidePlane = 12;
    downPlane = 12;
    upPlane = 12;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 286;

}
block_t WheatBlock1::getID(){ return 134;}

WheatBlock2::WheatBlock2():BaseBlock()
{
    textureRow = 7;

    sidePlane = 13;
    downPlane = 13;
    upPlane = 13;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 286;

}
block_t WheatBlock2::getID(){ return 135;}

WheatBlock3::WheatBlock3():BaseBlock()
{
    textureRow = 7;

    sidePlane = 14;
    downPlane = 14;
    upPlane = 14;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 287;

}
block_t WheatBlock3::getID(){ return 136;}

//must be last
TrapDoor2::TrapDoor2():BaseBlock()
{
    textureRow = 8;

    upPlane = 12;
    downPlane = 12;
    sidePlane = 11;
    editable = true;
    transparent = true;
    lightSource = false;
    blockSpecial = true;
}
block_t TrapDoor2::getID(){ return 137;}


Door3::Door3():BaseBlock()
{
	textureRow = 3;

	upPlane = 11;
	downPlane = 11;
	sidePlane = 9;
	editable = true;
	transparent = true;
	blockSpecial = true;

}
block_t Door3::getID(){ return 138;}

Door4::Door4():BaseBlock()
{
	textureRow = 4;

	upPlane = 9;
	downPlane = 9;
	sidePlane = 9;
	editable = true;
	transparent = true;
	blockSpecial = true;
}
block_t Door4::getID(){ return 139;}

Furnace2::Furnace2():BaseBlock()
{
    textureRow = 10;

    upPlane = 12;
    downPlane = 7;
    sidePlane = 9;
    editable = true;
    transparent = false;

}
block_t Furnace2::getID(){ return 140;}

Cloud::Cloud():BaseBlock()
{
    textureRow = 7;

    upPlane = 9;
    downPlane = 9;
    sidePlane = 9;
    editable = false;
    transparent = true;

}
block_t Cloud::getID(){ return 141;}

IronBlock::IronBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 1;
	editable = true;;
	transparent = false;
	soundType = 2;

}
block_t IronBlock::getID(){ return 142;}
