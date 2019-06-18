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
 15;
 -0.00087;-0.00412;-0.19473;,
 0.20773;-0.00412;0.01387;,
 0.29413;-0.21272;0.01387;,
 -0.00087;-0.21272;-0.28114;,
 -0.00087;-0.00412;0.22246;,
 -0.00087;-0.21272;0.30887;,
 -0.20946;-0.00412;0.01387;,
 -0.29587;-0.21272;0.01387;,
 -0.00087;-0.00412;-0.19473;,
 -0.00087;-0.21272;-0.28114;,
 0.20773;-0.42131;0.01387;,
 -0.00087;-0.42131;-0.19473;,
 -0.00087;-0.42131;0.22246;,
 -0.20946;-0.42131;0.01387;,
 -0.00087;-0.42131;-0.19473;;
 
 8;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;3,2,10,11;,
 4;2,5,12,10;,
 4;5,7,13,12;,
 4;7,9,14,13;;
 
 MeshMaterialList {
  10;
  8;
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
    "Player/body.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Player/thight.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Player/glove.jpg";
   }
  }
  Material {
   0.360800;0.458400;0.501600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.272800;0.344800;0.380000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.235200;0.235200;0.235200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
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
   0.800000;0.680800;0.520800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.558400;0.395200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  12;
  0.678595;0.281083;-0.678603;,
  0.678595;0.281080;0.678603;,
  -0.678598;0.281089;0.678597;,
  0.707103;-0.000002;-0.707111;,
  0.707103;-0.000004;0.707111;,
  -0.707107;-0.000002;0.707107;,
  0.678594;-0.281087;-0.678602;,
  0.678594;-0.281087;0.678602;,
  -0.678597;-0.281093;0.678597;,
  -0.678598;0.281089;-0.678597;,
  -0.707107;-0.000002;-0.707107;,
  -0.678597;-0.281093;-0.678597;;
  8;
  4;0,0,3,3;,
  4;1,1,4,4;,
  4;2,2,5,5;,
  4;9,9,10,10;,
  4;3,3,6,6;,
  4;4,4,7,7;,
  4;5,5,8,8;,
  4;10,10,11,11;;
 }
 MeshTextureCoords {
  15;
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.750000;0.250000;,
  0.750000;0.500000;,
  1.000000;0.250000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;;
 }
}
