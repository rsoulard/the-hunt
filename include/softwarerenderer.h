typedef struct SoftwareRenderer* softwareRenderer_t;

softwareRenderer_t SoftwareRenderer_New(int temp);
void SoftwareRenderer_Destroy(softwareRenderer_t this);
void SoftwareRenderer_Test(softwareRenderer_t this, int new);
