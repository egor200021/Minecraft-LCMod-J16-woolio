#ifndef SKYCLOUDS_H_
#define SKYCLOUDS_H_

#include <Aurora/Math/Vector3.h>
#include <Aurora/Graphics/Vertex.h>
#include <pspmath.h>

namespace Aurora
{
	namespace Graphics
	{
		class SkyClouds
		{
		public:
			SkyClouds();
			~SkyClouds();

			void SetTexture(int texture);
			void UpdateClouds();

			void Render();

		private:

			TexturesPSPVertex *cloudsVertices;
			int textureNumber;


		};
	}
}

#endif

