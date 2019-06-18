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
 35;
 0.00000;0.01170;-0.62791;,
 0.00000;0.06858;-0.62791;,
 0.04022;0.05192;-0.62791;,
 0.00000;0.01170;-0.62791;,
 0.05688;0.01170;-0.62791;,
 0.00000;0.01170;-0.62791;,
 0.04022;-0.02852;-0.62791;,
 0.00000;0.01170;-0.62791;,
 -0.00000;-0.04517;-0.62791;,
 0.00000;0.01170;-0.62791;,
 -0.04022;-0.02852;-0.62791;,
 0.00000;0.01170;-0.62791;,
 -0.05688;0.01170;-0.62791;,
 0.00000;0.01170;-0.62791;,
 -0.04022;0.05192;-0.62791;,
 0.00000;0.01170;-0.62791;,
 0.00000;0.06858;-0.62791;,
 -0.04022;0.05192;-0.56929;,
 -0.05688;0.01170;-0.56929;,
 -0.05688;0.01170;0.00000;,
 -0.04022;0.05192;0.00000;,
 0.00000;0.06858;0.00000;,
 0.00000;0.06858;-0.56929;,
 -0.04022;-0.02852;-0.56929;,
 -0.04022;-0.02852;0.00000;,
 0.00000;0.06858;-0.56929;,
 0.00000;0.06858;0.00000;,
 0.04022;0.05192;0.00000;,
 0.04022;0.05192;-0.56929;,
 -0.00000;-0.04517;-0.56929;,
 -0.00000;-0.04517;0.00000;,
 0.05688;0.01170;0.00000;,
 0.05688;0.01170;-0.56929;,
 0.04022;-0.02852;-0.56929;,
 0.04022;-0.02852;-0.00000;;
 
 24;
 3;0,1,2;,
 3;3,2,4;,
 3;5,4,6;,
 3;7,6,8;,
 3;9,8,10;,
 3;11,10,12;,
 3;13,12,14;,
 3;15,14,16;,
 4;17,14,12,18;,
 4;17,18,19,20;,
 4;17,20,21,22;,
 4;17,22,16,14;,
 4;18,12,10,23;,
 4;18,23,24,19;,
 4;25,26,27,28;,
 4;25,28,2,1;,
 4;23,10,8,29;,
 4;23,29,30,24;,
 4;28,27,31,32;,
 4;28,32,4,2;,
 4;29,8,6,33;,
 4;29,33,34,30;,
 4;32,31,34,33;,
 4;32,33,6,4;;
 
 MeshMaterialList {
  2;
  24;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.059608;0.012549;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  25;
  0.000000;1.000000;0.000000;,
  0.707087;0.707126;-0.000000;,
  1.000000;-0.000007;-0.000000;,
  0.707071;-0.707142;-0.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.707071;-0.707142;-0.000000;,
  -1.000000;-0.000007;-0.000000;,
  -0.707087;0.707126;-0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.707087;0.707126;0.000000;,
  -1.000000;-0.000007;0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.707071;-0.707142;0.000000;,
  0.707087;0.707126;0.000000;,
  -0.000000;-1.000000;-0.000000;,
  1.000000;-0.000007;0.000000;,
  0.707071;-0.707142;0.000000;,
  -0.707087;0.707126;0.000000;,
  -1.000000;-0.000007;0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.707071;-0.707142;0.000000;,
  0.707087;0.707126;0.000000;,
  -0.000000;-1.000000;-0.000000;,
  1.000000;-0.000007;0.000000;,
  0.707071;-0.707142;0.000000;;
  24;
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  4;9,17,18,10;,
  4;9,10,6,7;,
  4;9,7,0,11;,
  4;9,11,19,17;,
  4;10,18,20,12;,
  4;10,12,5,6;,
  4;11,0,1,13;,
  4;11,13,21,19;,
  4;12,20,22,14;,
  4;12,14,4,5;,
  4;13,1,2,15;,
  4;13,15,23,21;,
  4;14,22,24,16;,
  4;14,16,3,4;,
  4;15,2,3,16;,
  4;15,16,24,23;;
 }
 MeshTextureCoords {
  35;
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.875000;0.906637;,
  0.750000;0.906637;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.906637;,
  0.625000;0.906637;,
  0.625000;0.000000;,
  0.000000;0.906637;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.906637;,
  0.500000;0.906637;,
  0.500000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.906637;,
  0.375000;0.906637;,
  0.375000;0.000000;;
 }
}