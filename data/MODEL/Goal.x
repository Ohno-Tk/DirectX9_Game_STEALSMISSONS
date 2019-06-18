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
 20;
 -2.30052;17.50698;-2.68719;,
 2.30052;17.50698;-2.68719;,
 1.21684;4.27241;-1.22904;,
 -1.21684;4.27241;-1.22904;,
 2.35624;18.01779;-2.38347;,
 -2.35624;18.01779;-2.38347;,
 2.66052;17.50698;-2.32719;,
 -2.66052;17.50698;-2.32719;,
 2.66052;17.50698;2.32719;,
 1.21684;4.27241;1.22904;,
 2.35624;18.01779;2.38347;,
 2.30052;17.50698;2.68719;,
 -2.30052;17.50698;2.68719;,
 -1.21684;4.27241;1.22904;,
 -2.35624;18.01779;2.38347;,
 -2.66052;17.50698;2.32719;,
 -10.00000;0.97056;10.00000;,
 10.00000;0.97056;10.00000;,
 10.00000;0.97056;-10.00000;,
 -10.00000;0.97056;-10.00000;;
 
 18;
 4;0,1,2,3;,
 4;4,1,0,5;,
 3;2,1,6;,
 3;7,0,3;,
 3;7,5,0;,
 3;4,6,1;,
 4;6,8,9,2;,
 4;10,8,6,4;,
 3;9,8,11;,
 3;10,11,8;,
 4;11,12,13,9;,
 4;14,12,11,10;,
 3;13,12,15;,
 3;14,15,12;,
 4;15,7,3,13;,
 4;5,7,15,14;,
 4;14,10,4,5;,
 4;16,17,18,19;;
 
 MeshMaterialList {
  2;
  18;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1;;
  Material {
   0.000000;0.577255;0.800000;0.450000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Goal/GoalUI.png";
   }
  }
 }
 MeshNormals {
  20;
  -0.378749;-0.131940;-0.916046;,
  0.378749;-0.131940;-0.916046;,
  0.916127;-0.131362;0.378756;,
  -0.378749;-0.131940;0.916046;,
  -0.385602;0.166601;-0.907500;,
  0.385602;0.166601;-0.907500;,
  0.907409;0.167098;-0.385599;,
  0.907409;0.167098;0.385599;,
  0.385602;0.166601;0.907500;,
  -0.385602;0.166601;0.907500;,
  -0.907409;0.167098;0.385599;,
  -0.907409;0.167098;-0.385599;,
  -0.478850;0.735718;0.478980;,
  0.478850;0.735718;0.478980;,
  0.478850;0.735718;-0.478980;,
  -0.478850;0.735718;-0.478980;,
  0.994103;-0.108441;-0.000000;,
  0.000000;-0.109515;0.993985;,
  -0.994103;-0.108441;0.000000;,
  0.000000;1.000000;0.000000;;
  18;
  4;4,5,1,0;,
  4;14,5,4,15;,
  3;1,5,6;,
  3;11,4,0;,
  3;11,15,4;,
  3;14,6,5;,
  4;6,7,2,16;,
  4;13,7,6,14;,
  3;2,7,8;,
  3;13,8,7;,
  4;8,9,3,17;,
  4;12,9,8,13;,
  3;3,9,10;,
  3;12,10,9;,
  4;10,11,18,18;,
  4;15,11,10,12;,
  4;12,13,14,15;,
  4;19,19,19,19;;
 }
 MeshTextureCoords {
  20;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
