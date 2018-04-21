xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 26;
 -18.33639;10.00000;-10.00000;,
 0.00000;10.00000;-21.02818;,
 0.00000;-10.00000;-21.02818;,
 -18.33639;-10.00000;-10.00000;,
 17.55269;10.00000;-10.00000;,
 17.55269;-10.00000;-10.00000;,
 17.55269;10.00000;-10.00000;,
 17.55269;10.00000;10.00000;,
 17.55269;-10.00000;10.00000;,
 17.55269;-10.00000;-10.00000;,
 17.55269;10.00000;10.00000;,
 0.00000;10.00000;20.82511;,
 0.00000;-10.00000;20.82511;,
 17.55269;-10.00000;10.00000;,
 -18.33639;10.00000;10.00000;,
 -18.33639;-10.00000;10.00000;,
 -18.33639;10.00000;10.00000;,
 -18.33639;10.00000;-10.00000;,
 -18.33639;-10.00000;-10.00000;,
 -18.33639;-10.00000;10.00000;,
 0.00000;10.00000;-21.02818;,
 -18.33639;10.00000;-10.00000;,
 17.55269;10.00000;-10.00000;,
 -18.33639;-10.00000;-10.00000;,
 0.00000;-10.00000;-21.02818;,
 17.55269;-10.00000;-10.00000;;
 
 10;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;10,11,12,13;,
 4;11,14,15,12;,
 4;16,17,18,19;,
 4;16,11,20,21;,
 4;11,7,22,20;,
 4;23,24,12,19;,
 4;24,25,8,12;;
 
 MeshMaterialList {
  1;
  10;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\block003.jpg";
   }
  }
 }
 MeshNormals {
  10;
  -0.870460;0.000000;-0.492239;,
  -0.515401;0.000000;-0.856949;,
  0.875214;0.000000;-0.483735;,
  0.873190;0.000000;0.487380;,
  0.524922;0.000000;0.851150;,
  -0.868441;0.000000;0.495792;,
  0.532001;0.000000;-0.846744;,
  -0.508380;0.000000;0.861133;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  10;
  4;0,1,1,0;,
  4;6,2,2,6;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;7,5,5,7;,
  4;5,0,0,5;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;9,9,9,9;;
 }
 MeshTextureCoords {
  26;
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;;
 }
}
