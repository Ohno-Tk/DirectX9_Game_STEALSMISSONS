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
 102;
 -1.06417;3.10422;-0.87876;,
 -0.58258;3.30642;-0.96757;,
 -0.61375;2.27022;-1.21083;,
 -1.17337;2.21248;-0.96757;,
 0.00910;3.36718;-0.99426;,
 0.00910;2.29679;-1.27687;,
 0.60077;3.30642;-0.96757;,
 0.63195;2.27022;-1.21083;,
 1.08236;3.10422;-0.87876;,
 1.19157;2.21248;-0.96757;,
 -0.62811;1.11691;-1.27687;,
 -1.20618;1.11691;-0.99426;,
 0.00910;1.11691;-1.36275;,
 0.64631;1.11691;-1.27687;,
 1.22438;1.11691;-0.99426;,
 -0.61375;-0.03638;-1.21083;,
 -1.17337;0.02134;-0.96757;,
 0.00910;-0.06297;-1.27687;,
 0.63195;-0.03638;-1.21083;,
 1.19157;0.02134;-0.96757;,
 1.08236;3.10422;-0.87876;,
 1.19157;3.30642;-0.48706;,
 1.49064;2.27022;-0.51241;,
 1.19157;2.21248;-0.96757;,
 1.22438;3.36718;-0.00582;,
 1.57183;2.29679;-0.00582;,
 1.19157;3.30642;0.47543;,
 1.49064;2.27022;0.50078;,
 1.08236;3.10422;0.86713;,
 1.19157;2.21248;0.95595;,
 1.57183;1.11691;-0.52409;,
 1.22438;1.11691;-0.99426;,
 1.67742;1.11691;-0.00582;,
 1.57183;1.11691;0.51246;,
 1.22438;1.11691;0.98263;,
 1.49064;-0.03638;-0.51241;,
 1.19157;0.02134;-0.96757;,
 1.57183;-0.06297;-0.00582;,
 1.49064;-0.03638;0.50078;,
 1.19157;0.02134;0.95595;,
 1.08236;3.10422;0.86713;,
 0.60077;3.30642;0.95595;,
 0.63195;2.27022;1.19920;,
 1.19157;2.21248;0.95595;,
 0.00910;3.36718;0.98263;,
 0.00910;2.29679;1.26524;,
 -0.58258;3.30642;0.95595;,
 -0.61375;2.27022;1.19920;,
 -1.06417;3.10422;0.86713;,
 -1.17337;2.21248;0.95595;,
 0.64631;1.11691;1.26524;,
 1.22438;1.11691;0.98263;,
 0.00910;1.11691;1.35112;,
 -0.62811;1.11691;1.26524;,
 -1.20618;1.11691;0.98263;,
 0.63195;-0.03638;1.19920;,
 1.19157;0.02134;0.95595;,
 0.00910;-0.06297;1.26524;,
 -0.61375;-0.03638;1.19920;,
 -1.17337;0.02134;0.95595;,
 -1.06417;3.10422;0.86713;,
 -1.17337;3.30642;0.47543;,
 -1.47244;2.27022;0.50078;,
 -1.17337;2.21248;0.95595;,
 -1.20618;3.36718;-0.00582;,
 -1.55364;2.29679;-0.00582;,
 -1.17337;3.30642;-0.48706;,
 -1.47244;2.27022;-0.51241;,
 -1.06417;3.10422;-0.87876;,
 -1.17337;2.21248;-0.96757;,
 -1.55364;1.11691;0.51246;,
 -1.20618;1.11691;0.98263;,
 -1.65923;1.11691;-0.00582;,
 -1.55364;1.11691;-0.52409;,
 -1.20618;1.11691;-0.99426;,
 -1.47244;-0.03638;0.50078;,
 -1.17337;0.02134;0.95595;,
 -1.55364;-0.06297;-0.00582;,
 -1.47244;-0.03638;-0.51241;,
 -1.17337;0.02134;-0.96757;,
 -0.58258;3.30642;0.95595;,
 -0.61375;3.86019;0.56805;,
 -1.17337;3.30642;0.47543;,
 0.00910;4.01055;0.58128;,
 0.60077;3.30642;0.95595;,
 0.63195;3.86019;0.56805;,
 1.19157;3.30642;0.47543;,
 -0.62811;4.01055;-0.00582;,
 -1.20618;3.36718;-0.00582;,
 0.00910;4.20604;-0.00582;,
 0.64631;4.01055;-0.00582;,
 1.22438;3.36718;-0.00582;,
 -0.61375;3.86019;-0.57969;,
 -1.17337;3.30642;-0.48706;,
 0.00910;4.01055;-0.59292;,
 0.63195;3.86019;-0.57969;,
 1.19157;3.30642;-0.48706;,
 -0.58258;3.30642;-0.96757;,
 -1.06417;3.10422;-0.87876;,
 0.00910;3.36718;-0.99426;,
 0.60077;3.30642;-0.96757;,
 1.08236;3.10422;-0.87876;;
 
 64;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;3,2,10,11;,
 4;2,5,12,10;,
 4;5,7,13,12;,
 4;7,9,14,13;,
 4;11,10,15,16;,
 4;10,12,17,15;,
 4;12,13,18,17;,
 4;13,14,19,18;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;23,22,30,31;,
 4;22,25,32,30;,
 4;25,27,33,32;,
 4;27,29,34,33;,
 4;31,30,35,36;,
 4;30,32,37,35;,
 4;32,33,38,37;,
 4;33,34,39,38;,
 4;40,41,42,43;,
 4;41,44,45,42;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;43,42,50,51;,
 4;42,45,52,50;,
 4;45,47,53,52;,
 4;47,49,54,53;,
 4;51,50,55,56;,
 4;50,52,57,55;,
 4;52,53,58,57;,
 4;53,54,59,58;,
 4;60,61,62,63;,
 4;61,64,65,62;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;63,62,70,71;,
 4;62,65,72,70;,
 4;65,67,73,72;,
 4;67,69,74,73;,
 4;71,70,75,76;,
 4;70,72,77,75;,
 4;72,73,78,77;,
 4;73,74,79,78;,
 4;60,80,81,82;,
 4;80,44,83,81;,
 4;44,84,85,83;,
 4;84,28,86,85;,
 4;82,81,87,88;,
 4;81,83,89,87;,
 4;83,85,90,89;,
 4;85,86,91,90;,
 4;88,87,92,93;,
 4;87,89,94,92;,
 4;89,90,95,94;,
 4;90,91,96,95;,
 4;93,92,97,98;,
 4;92,94,99,97;,
 4;94,95,100,99;,
 4;95,96,101,100;;
 
 MeshMaterialList {
  9;
  64;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  73;
  -0.601305;0.360186;-0.713230;,
  -0.272838;0.414728;-0.868079;,
  0.000000;0.402168;-0.915566;,
  0.272837;0.414727;-0.868079;,
  0.601301;0.360186;-0.713234;,
  -0.640471;0.129853;-0.756924;,
  -0.246316;0.136493;-0.959530;,
  0.000000;0.155419;-0.987849;,
  0.246316;0.136494;-0.959530;,
  0.640471;0.129853;-0.756925;,
  -0.641744;-0.000000;-0.766919;,
  -0.274730;-0.000000;-0.961521;,
  0.000000;-0.000000;-1.000000;,
  0.274730;-0.000000;-0.961521;,
  0.641747;-0.000000;-0.766916;,
  -0.640927;-0.050464;-0.765942;,
  -0.274293;-0.056408;-0.959990;,
  0.000000;-0.065729;-0.997837;,
  0.274293;-0.056408;-0.959990;,
  0.640929;-0.050463;-0.765939;,
  0.799830;0.475807;-0.365896;,
  0.864864;0.502006;-0.000001;,
  0.799831;0.475809;0.365891;,
  0.601304;0.360189;0.713230;,
  0.922851;0.162613;-0.349146;,
  0.981899;0.189404;-0.000002;,
  0.922852;0.162614;0.349143;,
  0.640471;0.129853;0.756925;,
  0.922043;-0.000000;-0.387088;,
  1.000000;-0.000000;-0.000002;,
  0.922044;-0.000000;0.387084;,
  0.641746;-0.000000;0.766917;,
  0.919977;-0.066902;-0.386221;,
  0.996736;-0.080736;-0.000002;,
  0.919979;-0.066901;0.386217;,
  0.640929;-0.050459;0.765940;,
  0.272835;0.414732;0.868077;,
  0.000000;0.402174;0.915563;,
  -0.272836;0.414733;0.868077;,
  -0.601308;0.360189;0.713227;,
  0.246313;0.136492;0.959531;,
  0.000000;0.155417;0.987849;,
  -0.246312;0.136491;0.959531;,
  -0.640472;0.129852;0.756924;,
  0.274727;-0.000000;0.961522;,
  0.000000;-0.000000;1.000000;,
  -0.274727;-0.000000;0.961522;,
  -0.641743;-0.000000;0.766919;,
  0.274290;-0.056406;0.959991;,
  0.000000;-0.065729;0.997837;,
  -0.274290;-0.056406;0.959991;,
  -0.640926;-0.050461;0.765942;,
  -0.799831;0.475810;0.365889;,
  -0.864863;0.502008;-0.000001;,
  -0.799830;0.475808;-0.365893;,
  -0.922850;0.162615;0.349146;,
  -0.981898;0.189408;-0.000002;,
  -0.922849;0.162615;-0.349150;,
  -0.922041;-0.000000;0.387092;,
  -1.000000;-0.000000;-0.000002;,
  -0.922040;-0.000000;-0.387096;,
  -0.919975;-0.066904;0.386225;,
  -0.996735;-0.080741;-0.000002;,
  -0.919973;-0.066906;-0.386229;,
  -0.429935;0.746460;0.507892;,
  0.000000;0.799174;0.601099;,
  0.429935;0.746458;0.507894;,
  -0.520420;0.853910;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.520420;0.853910;-0.000000;,
  -0.429936;0.746455;-0.507897;,
  0.000000;0.799169;-0.601106;,
  0.429936;0.746454;-0.507900;;
  64;
  4;0,1,6,5;,
  4;1,2,7,6;,
  4;2,3,8,7;,
  4;3,4,9,8;,
  4;5,6,11,10;,
  4;6,7,12,11;,
  4;7,8,13,12;,
  4;8,9,14,13;,
  4;10,11,16,15;,
  4;11,12,17,16;,
  4;12,13,18,17;,
  4;13,14,19,18;,
  4;4,20,24,9;,
  4;20,21,25,24;,
  4;21,22,26,25;,
  4;22,23,27,26;,
  4;9,24,28,14;,
  4;24,25,29,28;,
  4;25,26,30,29;,
  4;26,27,31,30;,
  4;14,28,32,19;,
  4;28,29,33,32;,
  4;29,30,34,33;,
  4;30,31,35,34;,
  4;23,36,40,27;,
  4;36,37,41,40;,
  4;37,38,42,41;,
  4;38,39,43,42;,
  4;27,40,44,31;,
  4;40,41,45,44;,
  4;41,42,46,45;,
  4;42,43,47,46;,
  4;31,44,48,35;,
  4;44,45,49,48;,
  4;45,46,50,49;,
  4;46,47,51,50;,
  4;39,52,55,43;,
  4;52,53,56,55;,
  4;53,54,57,56;,
  4;54,0,5,57;,
  4;43,55,58,47;,
  4;55,56,59,58;,
  4;56,57,60,59;,
  4;57,5,10,60;,
  4;47,58,61,51;,
  4;58,59,62,61;,
  4;59,60,63,62;,
  4;60,10,15,63;,
  4;39,38,64,52;,
  4;38,37,65,64;,
  4;37,36,66,65;,
  4;36,23,22,66;,
  4;52,64,67,53;,
  4;64,65,68,67;,
  4;65,66,69,68;,
  4;66,22,21,69;,
  4;53,67,70,54;,
  4;67,68,71,70;,
  4;68,69,72,71;,
  4;69,21,20,72;,
  4;54,70,1,0;,
  4;70,71,2,1;,
  4;71,72,3,2;,
  4;72,20,4,3;;
 }
 MeshTextureCoords {
  102;
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
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
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
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
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
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
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
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
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
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
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;;
 }
}