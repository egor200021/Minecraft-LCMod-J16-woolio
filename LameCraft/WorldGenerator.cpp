#include "WorldGenerator.h"
#include "CraftWorld2.h"

#include <noisepp/Noise.h>
#include <noisepp/NoiseUtils.h>
#include <noisepp/NoiseBuilders.h>

void WorldGenerator::initRandompMap(int worldSize,int chunkSize, CraftWorld *world)
{
    //inicjuj mape
    int WORLD_SIZE = worldSize;
    int CHUNK_SIZE = chunkSize;

    //srand(time(NULL));
    int seed = rand() % 10000;

    //terrain settings for default terrain
    unsigned char grass = 1;
    unsigned char rock = 3;
    unsigned char dirt = 2;
    unsigned char water = 4;
    unsigned char sandUnderWater = 7;

    int terrainType = 0;//rand() % 3;//0-2

    int testterrain = rand() % 10;

    if(testterrain < 4)
        terrainType = 0;
    if(testterrain >= 4 && testterrain < 7)
        terrainType = 1;
    if(testterrain >=7)
        terrainType = 2;

    noisepp::PerlinModule perlin;
    perlin.setSeed(seed);
    perlin.setOctaveCount(4);
    perlin.setQuality(noisepp::NOISE_QUALITY_FAST_STD);

    float *data = new float[worldSize * worldSize];

    noisepp::utils::PlaneBuilder2D builder;
    builder.setModule(perlin);
    builder.setSize(worldSize, worldSize);
    if(terrainType == 2)
        builder.setBounds(0.0, 0.0, 2.0, 3.0);
    else if(terrainType == 2)
        builder.setBounds(0.0, 0.0, 0.5, 1.0);
    else if(terrainType == 9)
        builder.setBounds(0.0, 0.0, 1.0, 0.5);
    else
        builder.setBounds(0.0, 0.0, 4.0, 4.0);
    builder.setDestination(data);
    builder.build ();

    //build map
    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            int Height  = data[x + z*WORLD_SIZE]* WORLD_SIZE/12 + WORLD_SIZE/2;
            //int Height = m_HeightMap.GetValue(x, z) * WORLD_SIZE/12 + WORLD_SIZE/2;

            for (int y = 0; y < Height; ++y)
            {
                if(y == Height-1)
                    world->GetBlock(x, y, z) = grass;//grass
                else if(y < Height-3)
                    world->GetBlock(x, y, z) = rock;
                else
                    world->GetBlock(x, y, z) = dirt;
            }
        }
    }


    //carve terrain
    /*
    float *data2 = new float[worldSize * worldSize];
    float *data3 = new float[worldSize * worldSize];

    perlin.setSeed(seed+1);
    noisepp::utils::PlaneBuilder2D builder2;
    builder2.setModule(perlin);
    builder2.setSize(worldSize, worldSize);
    builder2.setBounds(0.0, 0.0, 4.0, 4.0);
    builder2.setDestination(data2);
    builder2.build ();

    perlin.setSeed(seed+2);
    noisepp::utils::PlaneBuilder2D builder3;
    builder3.setModule(perlin);
    builder3.setSize(worldSize, worldSize);
    builder3.setBounds(0.0, 0.0, 4.0, 4.0);
    builder3.setDestination(data3);
    builder3.build ();

    int height1= 0;
    int height2= 0;

    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            height1 = data2[x + z*WORLD_SIZE]* 10 + WORLD_SIZE/2;
            height2 = data3[x + z*WORLD_SIZE]* 12 + WORLD_SIZE/2;

            if (height2 > height1)
            {
                //put at height1 grass
                if(world->GetBlock(x, height1, z) != 0)
                    world->GetBlock(x, height1, z) = grass;

                //delete blocks
                for (int y = height1+1; y < height2; y++)
                {
                    world->GetBlock(x, y, z) = 0;
                }
            }
        }
    }


    //delete tempdata
    delete []data2;
    delete []data3;*/

    //caves?
   	noisepp::RidgedMultiModule NoiseSource;
	NoiseSource.setSeed(seed);//da looks interesting
	NoiseSource.setQuality(noisepp::NOISE_QUALITY_FAST_STD);
	NoiseSource.setOctaveCount(4);
	NoiseSource.setFrequency(1.5f);//the smaller the more dense and bigger 1.9
	NoiseSource.setLacunarity(2.5f);//the larger the number of the rarer objects 2.2

	noisepp::Pipeline3D *pipeline = new noisepp::Pipeline3D;
	noisepp::ElementID id = NoiseSource.addToPipeline(pipeline);
	noisepp::PipelineElement3D *element = pipeline->getElement(id);
	noisepp::Cache *cache = pipeline->createCache ();

	float nx, ny, nz;
	float max = 0.0f;

	for (int z = 2; z < WORLD_SIZE - 4; ++z)
	{
		for (int x = 2; x < WORLD_SIZE - 4; ++x)
		{
			for (int y = 2; y < WORLD_SIZE/2; ++y)
			{
				nx = (float)x / WORLD_SIZE;
				ny = (float)y / WORLD_SIZE;
				nz = (float)z / WORLD_SIZE;

				float test = element->getValue(nx,ny,nz,cache);

				if(test > max)
					max = test;

				if(test > 0.8f)
					if(world->GetBlock(x, y, z) != 0)
					{
						world->GetBlock(x, y, z) = 0;

					}

			}

		}
	}



    pipeline->freeCache (cache);
    cache = 0;
    delete pipeline;
    pipeline = 0;


    //watering

    int waterLevel = 62;

    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            int Height = data[x + z*WORLD_SIZE]* WORLD_SIZE/12 + WORLD_SIZE/2;
            //int Height = m_HeightMap.GetValue(x, z) * WORLD_SIZE/12 + WORLD_SIZE/2;

            if(Height < waterLevel)
            {
                world->GetBlock(x, Height-1, z) = sandUnderWater;//sand under water
                world->GetBlock(x, Height-2, z) = sandUnderWater;

                for (int y = Height; y < waterLevel; y++)
                {
                    world->GetBlock(x, y, z) = water;//water
                }

            }
            else if(Height == waterLevel)
            {
                world->GetBlock(x, Height-1, z) = sandUnderWater;//beach sand
                world->GetBlock(x, Height-2, z) = sandUnderWater;
            }
        }
    }


    //make the most bottom layer of cube not destroyable
    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            world->GetBlock(x, 0, z) = IronBlock::getID();
        }
    }

    delete []data;

    //init trees
    initTrees(WORLD_SIZE, terrainType, world);

    initPumpkins(WORLD_SIZE, terrainType, world);

    initTypes(WORLD_SIZE, terrainType, world);

    initIron(WORLD_SIZE, world);

    initCoal(WORLD_SIZE, world);

    initGold(WORLD_SIZE, world);

    initRedStone(WORLD_SIZE, world);

    initDiamond(WORLD_SIZE, world);

    initDirt(WORLD_SIZE, world);

    initCanes(WORLD_SIZE, world);
}

void WorldGenerator::initRandompMap(int worldSize,int chunkSize, CraftWorld *world, int terrainType,bool makeFlat,bool makeTrees,bool makePumpkins,bool makeTypes,bool makeIron,bool makeWater,bool makeCaves,bool makeCoal,bool makeGold,bool makeRedStone,bool makeDiamond,bool makeDirt,bool makeCanes,int seedII)
{
    //inicjuj mape
    int WORLD_SIZE = worldSize;
    int CHUNK_SIZE = chunkSize;

    int seed = seedII;

    //terrain settings for default terrain
    unsigned char grass = 1;
    unsigned char rock = 3;
    unsigned char dirt = 2;
    unsigned char water = 4;
    unsigned char sandUnderWater = 7;






    float *data = new float[worldSize * worldSize];

    //
    if(!makeFlat)
    {
        srand(seedII);
        noisepp::PerlinModule perlin;
        perlin.setSeed(seed);
        perlin.setQuality(noisepp::NOISE_QUALITY_FAST_STD);

        //data = new float[worldSize * worldSize];



        noisepp::utils::PlaneBuilder2D builder;
        builder.setModule(perlin);
        builder.setSize(worldSize, worldSize);
        if(terrainType == 2)
            builder.setBounds(0.0, 0.0, 2.0, 3.0);
        else if(terrainType == 2)
            builder.setBounds(0.0, 0.0, 0.5, 1.0);
        else if(terrainType == 9)
            builder.setBounds(0.0, 0.0, 1.0, 0.5);
        else
            builder.setBounds(0.0, 0.0, 4.0, 4.0);
        builder.setDestination(data);
        builder.build ();

        int Height = 64;

        //build map
        for (int z = 0; z < WORLD_SIZE; ++z)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                Height = data[x + z*WORLD_SIZE]* WORLD_SIZE/12 + WORLD_SIZE/2;
                //int Height = m_HeightMap.GetValue(x, z) * WORLD_SIZE/12 + WORLD_SIZE/2;

                for (int y = 0; y < Height; ++y)
                {
                    if(y == Height-1)
                        world->GetBlock(x, y, z) = grass;//grass
                    else if(y < Height-3)
                        world->GetBlock(x, y, z) = rock;
                    else
                        world->GetBlock(x, y, z) = dirt;
                }

            }
        }

        //carve terrain

        /*
        float *data2 = new float[worldSize * worldSize];
        float *data3 = new float[worldSize * worldSize];

        perlin.setSeed(seed+1);
        noisepp::utils::PlaneBuilder2D builder2;
        builder2.setModule(perlin);
        builder2.setSize(worldSize, worldSize);
        builder2.setBounds(0.0, 0.0, 4.0, 4.0);
        builder2.setDestination(data2);
        builder2.build ();

        perlin.setSeed(seed+2);
        noisepp::utils::PlaneBuilder2D builder3;
        builder3.setModule(perlin);
        builder3.setSize(worldSize, worldSize);
        builder3.setBounds(0.0, 0.0, 4.0, 4.0);
        builder3.setDestination(data3);
        builder3.build ();

        int height1= 0;
        int height2= 0;

        for (int z = 0; z < WORLD_SIZE; ++z)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                height1 = data2[x + z*WORLD_SIZE]* 10 + WORLD_SIZE/2;
                height2 = data3[x + z*WORLD_SIZE]* 12 + WORLD_SIZE/2;

                if (height2 > height1)
                {
                    //put at height1 grass
                    if(world->GetBlock(x, height1, z) != 0)
                        world->GetBlock(x, height1, z) = grass;

                    //delete blocks
                    for (int y = height1+1; y < height2; y++)
                    {
                        world->GetBlock(x, y, z) = 0;
                    }
                }
            }
        }


        //delete tempdata
        delete []data2;
        delete []data3;*/

    }
    else
    {
        noisepp::PerlinModule perlin;
        perlin.setSeed(seed);
        perlin.setQuality(noisepp::NOISE_QUALITY_FAST_STD);

        //data = new float[worldSize * worldSize];



        noisepp::utils::PlaneBuilder2D builder;
        builder.setModule(perlin);
        builder.setSize(worldSize, worldSize);

            builder.setBounds(0.0, 0.0, 0.0, 0.0);
        builder.setDestination(data);
        builder.build ();

        int Height = 50;

        //build map
        for (int z = 0; z < WORLD_SIZE; ++z)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                Height = data[x + z*WORLD_SIZE]* WORLD_SIZE/12 + WORLD_SIZE/2;
                //int Height = m_HeightMap.GetValue(x, z) * WORLD_SIZE/12 + WORLD_SIZE/2;

                for (int y = 0; y < Height; ++y)
                {
                        if(y == Height-1)
                            world->GetBlock(x, y, z) = grass;//grass
                        else if(y < Height-3)
                            world->GetBlock(x, y, z) = rock;
                        else
                            world->GetBlock(x, y, z) = dirt;
                }
            }
        }
    }

    //caves?
    if(makeCaves)
	{
		noisepp::RidgedMultiModule NoiseSource;
		NoiseSource.setSeed(seed);//wygl¹da ciekawie
		NoiseSource.setQuality(noisepp::NOISE_QUALITY_FAST_STD);
		NoiseSource.setOctaveCount(4);
		NoiseSource.setFrequency(1.5f);//im mniejsza tym bardziej gêste i wiêksze 1.9
		NoiseSource.setLacunarity(2.5f);//im wiêksza liczba tym rzadsze obiekty 2.2

		noisepp::Pipeline3D *pipeline = new noisepp::Pipeline3D;
		noisepp::ElementID id = NoiseSource.addToPipeline(pipeline);
		noisepp::PipelineElement3D *element = pipeline->getElement(id);
		noisepp::Cache *cache = pipeline->createCache ();

		float nx, ny, nz;

		for (int z = 2; z < WORLD_SIZE - 4; ++z)
		{
			for (int x = 2; x < WORLD_SIZE - 4; ++x)
			{
				for (int y = 2; y < WORLD_SIZE/2; ++y)
				{
					nx = (float)x / WORLD_SIZE;
					ny = (float)y / WORLD_SIZE;
					nz = (float)z / WORLD_SIZE;

					if(element->getValue(nx,ny,nz,cache) > 0.8f)
					{
						world->GetBlock(x, y, z) = 0;
					}
				}
			}
		}

		 pipeline->freeCache (cache);
		 cache = 0;
		 delete pipeline;
		 pipeline = 0;
	}


    //watering
    int waterLevel = 62;

    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            int Height = data[x + z*WORLD_SIZE]* WORLD_SIZE/12 + WORLD_SIZE/2;
            //int Height = m_HeightMap.GetValue(x, z) * WORLD_SIZE/12 + WORLD_SIZE/2;

            if(Height < waterLevel)
            {
                world->GetBlock(x, Height-1, z) = sandUnderWater;//sand under water

                for (int y = Height; y < waterLevel; y++)
                {
                    world->GetBlock(x, y, z) = water;//water
                }

            }
            else if(Height == waterLevel)
            {
                world->GetBlock(x, Height-1, z) = sandUnderWater;//beach sand

            }
            else if(Height == waterLevel + 1)
            {
                world->GetBlock(x, Height-1, z) = sandUnderWater;
            }

        }
    }

    delete []data;

    //make the most bottom layer of cube not destroyable
    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            world->GetBlock(x, 0, z) = IronBlock::getID();//last one in set
        }
    }

    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            short r = rand() % 2;
            if (r == 1)
            {
            world->GetBlock(x, 1, z) = IronBlock::getID();//last one in set
            }
        }
    }

    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            short r = rand() % 3;
            if (r == 1)
            {
            world->GetBlock(x, 2, z) = IronBlock::getID();//last one in set
            }
        }
    }

    //init trees
    if(makeTrees)
        initTrees(WORLD_SIZE, terrainType, world);

    if(makePumpkins)
    initPumpkins(WORLD_SIZE, terrainType, world);

    if(makeIron)
        initIron(WORLD_SIZE, world);

    if(makeCoal)
        initCoal(WORLD_SIZE, world);

    if(makeGold)
        initGold(WORLD_SIZE, world);

    if(makeRedStone)
        initRedStone(WORLD_SIZE, world);

    if(makeDiamond)
        initDiamond(WORLD_SIZE, world);

    if(makeDirt)
        initDirt(WORLD_SIZE, world);

    if(makeCanes)
        initCanes(WORLD_SIZE, world);

}
void WorldGenerator::initTrees(int WORLD_SIZE, int treeChoose, CraftWorld *world)
{
    unsigned short NumTrees = 0;
    unsigned short Forest;

    unsigned short gen_t = 0;
    for(int j = 1; j < 3; ++j)
    {
    for(int k = 1; k < 3; ++k)
    {
        Forest = rand() % 2;
        gen_t = rand() % 2;
        if (gen_t == 0)
        {
            continue;
        }
        NumTrees = 30 + rand() % 60;


    for (int i = 0; i < NumTrees; ++i)
    {

        //Choose the tree position
        int x = (j-1) * 63 + rand() % (j * 63);
        int z = (k-1) * 63 + rand() % (k * 63);
        int y = world->groundHeight(x, z);

        if (y <= 0) continue;

        int TrunkHeight = 5 + rand() % 1;//rand() % 5 + 4;

        if (Forest == 1)
        {
        //check if there is an water on there or another tree
        int flag = 1;
        for (int y1 = y; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            if(world->GetBlock(x, y1, z) == JungleLeaves::getID() ||world->GetBlock(x, y1, z) == Snow2::getID() || world->GetBlock(x, y1, z) == 4 || world->GetBlock(x, y1, z) == 3 || world->GetBlock(x, y1, z) == 8 || world->GetBlock(x, y1, z) == 9 || world->GetBlock(x, y1, z) == 31 || world->GetBlock(x, y1, z) == 38 || world->GetBlock(x, y1, z) == 25 || world->GetBlock(x, y1, z) == 32 || world->GetBlock(x, y1, z) == 80 || world->GetBlock(x, y1, z) == 78 || world->GetBlock(x, y1, z) == Cloud::getID())
                flag = 0;
        }

        if(flag == 0)continue;



            TrunkHeight = 5;
            //Create the tree trunk
            for (int y1 = y + 1; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
            {
                block_t& Block = world->GetBlock(x, y1, z);
                if (Block == 0) Block = 8;
            }

            //create my leaves
            for(int yy = 0; yy < 3; yy++)
            {
                for(int xx = 0; xx < 3; xx++)
                {
                    for(int zz = 0; zz < 3; zz++)
                    {
                        int x1 = xx + x - 1;// :D - what a shitty code
                        int y1 = yy + y + TrunkHeight - 1;
                        int z1 = zz + z - 1;

                        if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                        if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                        block_t& Block = world->GetBlock(x1, y1, z1);
                        if (Block == 0) Block = 9;
                    }

            }
        }
        }
        else
        {
        TrunkHeight = 8 + rand() % 2;
        int flag = 1;
        for (int y1 = y; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            if(world->GetBlock(x, y1, z) == JungleLeaves::getID() ||world->GetBlock(x, y1, z) == Snow2::getID() || world->GetBlock(x, y1, z) == 4 || world->GetBlock(x, y1, z) == 3 || world->GetBlock(x, y1, z) == 8 || world->GetBlock(x, y1, z) == 9 || world->GetBlock(x, y1, z) == 31 || world->GetBlock(x, y1, z) == 38 || world->GetBlock(x, y1, z) == 25 || world->GetBlock(x, y1, z) == 32 || world->GetBlock(x, y1, z) == 80 || world->GetBlock(x, y1, z) == 78 || world->GetBlock(x, y1, z) == Cloud::getID())
                flag = 0;
        }

        if(flag == 0)continue;




            //Create the tree trunk
            for (int y1 = y + 1; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
            {
                block_t& Block = world->GetBlock(x, y1, z);
                if (Block == 0) Block = 30;
            }

            for(int yy = 0; yy < 1; yy++)
            {
                for(int xx = 0; xx < 3; xx++)
                {
                    for(int zz = 0; zz < 3; zz++)
                    {
                        int x1 = xx + x - 1;// :D - what a shitty code
                        int y1 = yy + y + TrunkHeight + 1;
                        int z1 = zz + z - 1;

                        if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                        if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                        block_t& Block = world->GetBlock(x1, y1, z1);
                        if (Block == 0) Block = 9;
                    }
                }
            }

            for(int yy = 0; yy < 1; yy++)
            {
                for(int xx = 0; xx < 3; xx++)
                {
                    for(int zz = 0; zz < 3; zz++)
                    {
                        int x1 = xx + x - 1;// :D - what a shitty code
                        int y1 = yy + y + TrunkHeight - 1;
                        int z1 = zz + z - 1;

                        if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                        if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                        block_t& Block = world->GetBlock(x1, y1, z1);
                        if (Block == 0) Block = 9;
                    }
                }
            }

            for(int yy = 0; yy < 1; yy++)
            {
                for(int xx = 0; xx < 5; xx++)
                {
                    for(int zz = 0; zz < 5; zz++)
                    {
                        int x1 = xx + x - 2;// :D - what a shitty code
                        int y1 = yy + y + TrunkHeight;
                        int z1 = zz + z - 2;

                        if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                        if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                        block_t& Block = world->GetBlock(x1, y1, z1);
                        if (Block == 0) Block = 9;
                    }
                }
            }


        }
    }

            //create my leaves

        }


    }
}

void WorldGenerator::initPumpkins(int WORLD_SIZE, int PumpkinChoose, CraftWorld *world)
{
    int NumPumpkins = 5 + rand() % 10;

    for (int i = 0; i < NumPumpkins; ++i)
    {
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        //check if there is an water on there or another tree
        unsigned short rad = 0;

        if(PumpkinChoose == 0)
        {

                for(int x2 = x-3; x2 < x+3; ++x2)
                {
                    for(int z2 = z-3; z2 < z+3; ++z2)
                    {
                        if (x2 > 0 && x2 < 128 && z2 > 0 && z2 < 128)
                        {

                            rad = rand() % 9;

                            if (rad != 2)
                                continue;

                            if(world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 1 || world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 2)
                            {
                            short rad2 = rand() % 4;

                            switch(rad2)
                            {
                            case 0: world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)=74; break;
                            case 1: world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)=121; break;
                            case 2: world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)=122; break;
                            case 3: world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)=123; break;
                            }
                            }
                        }
                    }
                }


        }


    }
}


void WorldGenerator::initTypes(int WORLD_SIZE, int TypeChoose, CraftWorld *world)
{
    int NumTypes = 5+rand() % 20;

    for (int i = 0; i < NumTypes; ++i)
    {
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = world->groundHeight(x, z);

        if (y <= 0) continue;

        short rad2 = rand() % 4;
        short rad;
        if(TypeChoose == 0)
        {

                for(int x2 = x-4; x2 < x+4; ++x2)
                {
                    for(int z2 = z-4; z2 < z+4; ++z2)
                    {
                        if (x2 > 0 && x2 < 128 && z2 > 0 && z2 < 128)
                        {

                            rad = rand() % 10;

                            if (rad > 8)
                                continue;

                            if(world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 1 || world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 2)
                            {

                            switch(rad2)
                            {
                            case 2: world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)=119; break;
                            case 1: world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)=119; break;
                            case 3: world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)=119; break;
                            case 0: world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)=120; break;
                            }
                            }
                        }
                    }
                }


        }

       /* if(TypeChoose == 0)
        {
            for (int y1 = y + 1; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
            {
                block_t& Block = world->GetBlock(x, y1, z);
                if (Block == 0) Block = 30;
            }

            for(int yy = 0; yy < 1; yy++)
            {
                for(int xx = 0; xx < 3; xx++)
                {
                    for(int zz = 0; zz < 3; zz++)
                    {
                        int x1 = xx + x - 1;// :D - what a shitty code
                        int y1 = yy + y + TrunkHeight + 1;
                        int z1 = zz + z - 1;

                        if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                        if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                        block_t& Block = world->GetBlock(x1, y1, z1);
                        if (Block == 0) Block = 9;
                    }
                }
            }

            for(int yy = 0; yy < 1; yy++)
            {
                for(int xx = 0; xx < 3; xx++)
                {
                    for(int zz = 0; zz < 3; zz++)
                    {
                        int x1 = xx + x - 1;// :D - what a shitty code
                        int y1 = yy + y + TrunkHeight - 1;
                        int z1 = zz + z - 1;

                        if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                        if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                        block_t& Block = world->GetBlock(x1, y1, z1);
                        if (Block == 0) Block = 9;
                    }
                }
            }

            for(int yy = 0; yy < 1; yy++)
            {
                for(int xx = 0; xx < 5; xx++)
                {
                    for(int zz = 0; zz < 5; zz++)
                    {
                        int x1 = xx + x - 2;// :D - what a shitty code
                        int y1 = yy + y + TrunkHeight;
                        int z1 = zz + z - 2;

                        if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                        if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                        block_t& Block = world->GetBlock(x1, y1, z1);
                        if (Block == 0) Block = 9;
                    }
                }
            }

           //create my leaves

        }*/


    }
}

void WorldGenerator::initIron(int WORLD_SIZE, CraftWorld *world)
{
    int NumOres = 1800;

    for (int i = 0; i < NumOres; ++i)
    {
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = rand() % WORLD_SIZE;

        if (y <= 0) continue;

        int TrunkHeight = 1;//rand() % 5 + 4;

        int flag = 1;
        for (int y1 = y; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            if(world->GetBlock(x, y1, z) == 0 || world->GetBlock(x, y1, z) == Snow2::getID() || world->GetBlock(x, y1, z) == 96 || world->GetBlock(x, y1, z) == 4 || world->GetBlock(x, y1, z) == 8 || world->GetBlock(x, y1, z) == 9 || world->GetBlock(x, y1, z) == 31 || world->GetBlock(x, y1, z) == 38 || world->GetBlock(x, y1, z) == 25 || world->GetBlock(x, y1, z) == 32 || world->GetBlock(x, y1, z) == 80 || world->GetBlock(x, y1, z) == 78 || world->GetBlock(x, y1, z) == Cloud::getID())
                flag = 0;
        }

        if(flag == 0)continue;


        for (int y1 = y + 1; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            block_t& Block = world->GetBlock(x, y1, z);
            if (Block == RockBlock::getID()) Block = 41;
        }

        for(int yy = 0; yy < 2; yy++)
        {
            for(int xx = 0; xx < 3; xx++)
            {
                for(int zz = 0; zz < 3; zz++)
                {
                    int x1 = xx + x - 2;// :D - what a shitty code
                    int y1 = yy + y + TrunkHeight + 1;
                    int z1 = zz + z - 1;

                    if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                    if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                    block_t& Block = world->GetBlock(x1, y1, z1);
                    if (Block == RockBlock::getID()) Block = 41;
                }
            }
        }
    }
}

void WorldGenerator::initCoal(int WORLD_SIZE, CraftWorld *world)
{
    int NumOres = 2250;

    for (int i = 0; i < NumOres; ++i)
    {
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = rand() % WORLD_SIZE;

        int TrunkHeight = 1;

        if (y <= 0) continue;

        int flag = 1;
        for (int y1 = y; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            if(world->GetBlock(x, y1, z) == 0 || world->GetBlock(x, y1, z) == Snow2::getID() || world->GetBlock(x, y1, z) == 96 || world->GetBlock(x, y1, z) == 4 || world->GetBlock(x, y1, z) == 8 || world->GetBlock(x, y1, z) == 9 || world->GetBlock(x, y1, z) == 31 || world->GetBlock(x, y1, z) == 38 || world->GetBlock(x, y1, z) == 25 || world->GetBlock(x, y1, z) == 32 || world->GetBlock(x, y1, z) == 80 || world->GetBlock(x, y1, z) == 78 || world->GetBlock(x, y1, z) == Cloud::getID())
                flag = 0;
        }

        if(flag == 0)continue;




        for (int y1 = y + 1; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            block_t& Block = world->GetBlock(x, y1, z);
            if (Block == RockBlock::getID()) Block = 42;
        }



        for(int yy = 0; yy < 2; yy++)
        {
            for(int xx = 0; xx < 3; xx++)
            {
                for(int zz = 0; zz < 2; zz++)
                {
                    int x1 = xx + x - 2;// :D - what a shitty code
                    int y1 = yy + y + TrunkHeight - 4;
                    int z1 = zz + z - 1;

                    if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                    if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                    block_t& Block = world->GetBlock(x1, y1, z1);
                    if (Block == RockBlock::getID()) Block = 42;
                }
            }
        }


    }
}

void WorldGenerator::initGold(int WORLD_SIZE, CraftWorld *world)
{
    int NumOres = 500;

    for (int i = 0; i < NumOres; ++i)
    {
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = 17 - rand() % 17;

        int TrunkHeight = 1;

        if (y <= 0) continue;

        int flag = 1;
        for (int y1 = y; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            if(world->GetBlock(x, y1, z) == 0 || world->GetBlock(x, y1, z) == Snow2::getID() || world->GetBlock(x, y1, z) == 96 || world->GetBlock(x, y1, z) == 4 || world->GetBlock(x, y1, z) == 8 || world->GetBlock(x, y1, z) == 9 || world->GetBlock(x, y1, z) == 31 || world->GetBlock(x, y1, z) == 38 || world->GetBlock(x, y1, z) == 25 || world->GetBlock(x, y1, z) == 32 || world->GetBlock(x, y1, z) == 80 || world->GetBlock(x, y1, z) == 78 || world->GetBlock(x, y1, z) == Cloud::getID())
                flag = 0;
        }

        if(flag == 0)continue;




        for (int y1 = y + 1; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            block_t& Block = world->GetBlock(x, y1, z);
            if (Block == RockBlock::getID()) Block = 5;
        }

        for(int yy = 0; yy < 2; yy++)
        {
            for(int xx = 0; xx < 3; xx++)
            {
                for(int zz = 0; zz < 2; zz++)
                {
                    int x1 = xx + x - 2;// :D - what a shitty code
                    int y1 = yy + y + TrunkHeight + 1;
                    int z1 = zz + z - 1;

                    if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                    if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                    block_t& Block = world->GetBlock(x1, y1, z1);
                    if (Block == RockBlock::getID()) Block = 5;
                }
            }
        }
    }
}

void WorldGenerator::initRedStone(int WORLD_SIZE, CraftWorld *world)
{
    int NumOres = 700;

    for (int i = 0; i < NumOres; ++i)
    {
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = 17 - rand() % 17;

        int TrunkHeight = 1;

        if (y <= 0) continue;

        int flag = 1;
        for (int y1 = y; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            if(world->GetBlock(x, y1, z) == 0 || world->GetBlock(x, y1, z) == Snow2::getID() || world->GetBlock(x, y1, z) == 96 || world->GetBlock(x, y1, z) == 4 || world->GetBlock(x, y1, z) == 8 || world->GetBlock(x, y1, z) == 9 || world->GetBlock(x, y1, z) == 31 || world->GetBlock(x, y1, z) == 38 || world->GetBlock(x, y1, z) == 25 || world->GetBlock(x, y1, z) == 32 || world->GetBlock(x, y1, z) == 80 || world->GetBlock(x, y1, z) == 78 || world->GetBlock(x, y1, z) == Cloud::getID())
                flag = 0;
        }

        if(flag == 0)continue;




        for (int y1 = y + 1; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            block_t& Block = world->GetBlock(x, y1, z);
            if (Block == RockBlock::getID()) Block = 44;
        }

        for(int yy = 0; yy < 2; yy++)
        {
            for(int xx = 0; xx < 3; xx++)
            {
                for(int zz = 0; zz < 2; zz++)
                {
                    int x1 = xx + x - 2;// :D - what a shitty code
                    int y1 = yy + y + TrunkHeight + 1;
                    int z1 = zz + z - 1;

                    if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                    if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                    block_t& Block = world->GetBlock(x1, y1, z1);
                    if (Block == RockBlock::getID()) Block = 44;
                }
            }
        }
    }
}

void WorldGenerator::initDiamond(int WORLD_SIZE, CraftWorld *world)
{
    int NumOres = 200;

    for (int i = 0; i < NumOres; ++i)
    {
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = 10 - rand() % 10;

        int TrunkHeight = 1;

        if (y <= 0) continue;

        int flag = 1;
        for (int y1 = y; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            if(world->GetBlock(x, y1, z) == 0 || world->GetBlock(x, y1, z) == Snow2::getID() || world->GetBlock(x, y1, z) == 96 || world->GetBlock(x, y1, z) == 4 || world->GetBlock(x, y1, z) == 8 || world->GetBlock(x, y1, z) == 9 || world->GetBlock(x, y1, z) == 31 || world->GetBlock(x, y1, z) == 38 || world->GetBlock(x, y1, z) == 25 || world->GetBlock(x, y1, z) == 32 || world->GetBlock(x, y1, z) == 80 || world->GetBlock(x, y1, z) == 78 || world->GetBlock(x, y1, z) == Cloud::getID())
                flag = 0;
        }

        if(flag == 0)continue;




        for (int y1 = y + 1; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            block_t& Block = world->GetBlock(x, y1, z);
            if (Block == RockBlock::getID()) Block = 43;
        }

        for(int yy = 0; yy < 2; yy++)
        {
            for(int xx = 0; xx < 2; xx++)
            {
                for(int zz = 0; zz < 2; zz++)
                {
                    int x1 = xx + x - 2;// :D - what a shitty code
                    int y1 = yy + y + TrunkHeight + 1;
                    int z1 = zz + z - 1;

                    if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                    if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                    block_t& Block = world->GetBlock(x1, y1, z1);
                    if (Block == RockBlock::getID()) Block = 43;
                }
            }
        }
    }
}

void WorldGenerator::initDirt(int WORLD_SIZE, CraftWorld *world)
{
    int NumOres = 2000;

    for (int i = 0; i < NumOres; ++i)
    {
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = rand() % WORLD_SIZE;

        int TrunkHeight = 1;

        if (y <= 0) continue;

        int flag = 1;
        for (int y1 = y; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            if(world->GetBlock(x, y1, z) == 0 || world->GetBlock(x, y1, z) == Snow2::getID() || world->GetBlock(x, y1, z) == 96 || world->GetBlock(x, y1, z) == 4 || world->GetBlock(x, y1, z) == 8 || world->GetBlock(x, y1, z) == 9 || world->GetBlock(x, y1, z) == 31 || world->GetBlock(x, y1, z) == 38 || world->GetBlock(x, y1, z) == 25 || world->GetBlock(x, y1, z) == 32 || world->GetBlock(x, y1, z) == 80 || world->GetBlock(x, y1, z) == 78 || world->GetBlock(x, y1, z) == Cloud::getID())
                flag = 0;
        }

        if(flag == 0)continue;




        for (int y1 = y + 1; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            block_t& Block = world->GetBlock(x, y1, z);
            if (Block == RockBlock::getID()) Block = 2;
        }

        for(int yy = 0; yy < 4; yy++)
        {
            for(int xx = 0; xx < 5; xx++)
            {
                for(int zz = 0; zz < 4; zz++)
                {
                    int x1 = xx + x - 2;// :D - what a shitty code
                    int y1 = yy + y + TrunkHeight + 1;
                    int z1 = zz + z - 1;

                    if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                    if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                    block_t& Block = world->GetBlock(x1, y1, z1);
                    if (Block == RockBlock::getID()) Block = 2;
                }
            }
        }
    }
}

void WorldGenerator::initCanes(int WORLD_SIZE, CraftWorld *world)
{
    int NumCanes = 70;

    for (int i = 0; i < NumCanes; ++i)
    {
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = world->groundHeight(x, z);

        if (y <= 0) continue;

        int TrunkHeight = 3;//rand() % 5 + 4;


        //check if there is an water on there or another tree
        int flag = 1;
        for (int y1 = y; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {
            if(world->GetBlock(x, y1, z) == Cloud::getID() || world->GetBlock(x, y1, z) == 1 || world->GetBlock(x, y1, z) == JungleLeaves::getID() || world->GetBlock(x, y1, z) == 4 || world->GetBlock(x, y1, z) == 3 || world->GetBlock(x, y1, z) == 8 || world->GetBlock(x, y1, z) == 9 || world->GetBlock(x, y1, z) == 31 || world->GetBlock(x, y1, z) == 38 || world->GetBlock(x, y1, z) == 25 || world->GetBlock(x, y1, z) == 32 || world->GetBlock(x, y1, z) == 80 || world->GetBlock(x, y1, z) == 78 || world->GetBlock(x, y1, z) == 74)
                flag = 0;
        }

        if(flag == 0)continue;




        for (int y1 = y + 1; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
        {;
            if (world->GetBlock(x, y1, z) == 0)
            {
                world->GetBlock(x, y1, z) = 33;
            }
        }
    }
}




