#include <Aurora/Graphics/Effects/SkyClouds.h>
#include <Aurora/Graphics/TextureManager.h>


namespace Aurora
{
	namespace Graphics
	{
		SkyClouds::SkyClouds()
		{

			cloudsVertices = (TexturesPSPVertex*)memalign(16,4 * sizeof(TexturesPSPVertex));
		}

		SkyClouds::~SkyClouds()
		{
			free(cloudsVertices);
		}



		void SkyClouds::SetTexture(int texture)
		{
			textureNumber = texture;
		}

		void  SkyClouds::UpdateClouds()
		{
			ScePspFMatrix4 t;
			sceGumMatrixMode(GU_VIEW);
			sceGumStoreMatrix(&t);
			sceGumMatrixMode(GU_MODEL);

			//printf("angle: %f\n", angle);

			//float textureScale = 1.0f / stepScale;
			int i = 0;

			cloudsVertices[i].x = 0.0f;// * stepScale;
			cloudsVertices[i].y = 100.0f;// * stepScale;
			cloudsVertices[i].z = 0.0f;// * stepScale;
			cloudsVertices[i].u = 0.f;// * textureScale;
			cloudsVertices[i].v = 0.f;// * textureScale;
			i++;

			// (x, y - 1, z)
			cloudsVertices[i].x = 0.0f;// * stepScale;
			cloudsVertices[i].y = 100.0f;// * stepScale;
			cloudsVertices[i].z = 640.0f;// * stepScale;
			cloudsVertices[i].u = 0.f;// * textureScale;
			cloudsVertices[i].v = 1.f;// * textureScale;
			i++;

			// (x + 1, y, z)
			cloudsVertices[i].x = 640.0f;// * stepScale;
			cloudsVertices[i].y = 100.0f;// * stepScale;
			cloudsVertices[i].z = 0;// * stepScale;
			cloudsVertices[i].u = 1.f;// * textureScale;
			cloudsVertices[i].v = 0.f;// * textureScale;
			i++;

			// (x + 1, y - 1, z)
			cloudsVertices[i].x = 640.0f;// * stepScale;
			cloudsVertices[i].y = 100.0f;//* stepScale;
			cloudsVertices[i].z = 640.0f;// * stepScale;
			cloudsVertices[i].u = 1.f;// * textureScale;
			cloudsVertices[i].v = 1.f;// * textureScale;



			sceKernelDcacheWritebackInvalidateRange(cloudsVertices,4 * sizeof(CraftPSPVertex));
		}

		void SkyClouds::Render()
		{
			sceGuColor(0xFFFFFFFF);
			sceGuEnable(GU_TEXTURE_2D);
			sceGuEnable(GU_BLEND);

			sceGuBlendFunc(GU_ADD, GU_FIX,GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);

			Image* image = TextureManager::Instance()->Images[textureNumber];

			sceGuTexMode(image->ColorMode,0,0,image->Swizzle);
			sceGuTexFunc( GU_TFX_MODULATE, GU_TCC_RGBA);
			sceGuTexFilter(GU_LINEAR, GU_LINEAR);
			sceGuTexScale(1.0f, 1.0f);                // No scaling
			sceGuTexOffset(0.0f, 0.0f);
			sceGuTexImage(0,image->power2Width,image->power2Height,image->power2Width,image->ImageData);

			sceGumDrawArray(GU_TRIANGLE_STRIP, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, cloudsVertices);

			sceGuDisable(GU_TEXTURE_2D);
			sceGuDisable(GU_BLEND);

			//make default blend function
			sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
		}
	}
}

