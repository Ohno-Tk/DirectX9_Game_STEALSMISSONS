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
 21;
 0.24539;0.29622;0.01387;,
 0.45399;0.20982;0.01387;,
 0.24539;0.20982;-0.19473;,
 0.24539;0.29622;0.01387;,
 0.24539;0.20982;0.22246;,
 0.24539;0.29622;0.01387;,
 0.03679;0.20982;0.01387;,
 0.24539;0.29622;0.01387;,
 0.24539;0.20982;-0.19473;,
 0.54039;0.00122;0.01387;,
 0.24539;0.00122;-0.28114;,
 0.24539;0.00122;0.30886;,
 -0.04961;0.00122;0.01387;,
 0.24539;0.00122;-0.28114;,
 0.45399;-0.20737;0.01387;,
 0.24539;-0.20737;-0.19473;,
 0.24539;-0.20737;0.22246;,
 0.03679;-0.20737;0.01387;,
 0.24539;-0.20737;-0.19473;,
 0.24539;-0.29378;0.01387;,
 0.24539;-0.29378;0.01387;;
 
 14;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 4;2,1,9,10;,
 4;1,4,11,9;,
 4;4,6,12,11;,
 4;6,8,13,12;,
 4;10,9,14,15;,
 4;9,11,16,14;,
 4;11,12,17,16;,
 4;12,13,18,17;,
 3;16,17,19;,
 3;17,18,20;;
 
 MeshMaterialList {
  9;
  14;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Enemy/head.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Enemy/Enemybody.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Enemy/glove.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Enemy/Camo.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Enemy/camo_arm.jpg";
   }
  }
  Material {
   0.228800;0.150400;0.044000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.021600;0.021600;0.021600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   10.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  19;
  -0.000000;1.000000;0.000009;,
  0.267629;0.791454;-0.549522;,
  0.549527;0.791454;-0.267620;,
  0.267622;0.791443;0.549541;,
  -0.549521;0.791451;0.267641;,
  0.707113;-0.000009;-0.707101;,
  0.707092;-0.000005;0.707121;,
  -0.707092;-0.000005;0.707121;,
  0.678601;-0.281099;-0.678590;,
  0.678585;-0.281081;0.678613;,
  -0.549547;-0.791434;0.267640;,
  -0.382705;-0.923871;0.000008;,
  0.678587;0.281071;0.678615;,
  -0.678587;0.281071;0.678615;,
  -0.678604;0.281087;-0.678592;,
  -0.707113;-0.000006;-0.707101;,
  -0.557343;-0.615396;0.557367;,
  -0.557351;-0.615407;-0.557345;,
  -0.678601;-0.281099;-0.678589;;
  14;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,1,4;,
  4;1,2,5,5;,
  4;12,3,6,6;,
  4;13,4,7,7;,
  4;14,14,15,15;,
  4;5,5,8,8;,
  4;6,6,9,9;,
  4;7,7,10,16;,
  4;15,15,17,18;,
  3;16,10,11;,
  3;10,17,11;;
 }
 MeshTextureCoords {
  21;
  0.125000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.375000;0.000000;,
  0.500000;0.250000;,
  0.625000;0.000000;,
  0.750000;0.250000;,
  0.875000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.625000;1.000000;,
  0.875000;1.000000;;
 }
}
