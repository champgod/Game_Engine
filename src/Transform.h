

class Transform{
    public:
        void translate(float dx, float dy, float dz); // This function should be responsbile for translating objects.
        void rotate(float radX, float radY, float radZ); // This function should be responsible for handling rotation

        void setPosition(float posX, float posY, float posZ);
        void setRotation(float radX, float radY, float radZ);

        float getX() const;
        float getY() const;
        float getZ() const;

        float getRadX() const;
        float getRadY() const;
        float getRadZ() const;

    private:
        float posX = 0.0f;
        float posY = 0.0f;
        float posZ = 0.0f;

        float radX = 0.0f;
        float radY = 0.0f;
        float radZ = 0.0f;


};