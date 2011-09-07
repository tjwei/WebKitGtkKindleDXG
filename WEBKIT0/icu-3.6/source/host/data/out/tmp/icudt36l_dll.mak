## Makefile for icudt36l created by pkgdata
## from ICU Version 3.6

NAME=icudt36l
LIBNAME=icudata
CNAME=icudt36l
TARGETDIR=../lib
TEMP_DIR=./out/tmp
srcdir=$(TEMP_DIR)
SRCDIR=/home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l
MODE=dll
MAKEFILE=./out/tmp/icudt36l_dll.mak
ENTRYPOINT=icudt36
include ../data/icupkg.inc



TEMP_PATH=$(TEMP_DIR)/
TARG_PATH=$(TARGETDIR)/
## List files [1] containing data files to process (note: - means stdin)
LISTFILES= ./out/tmp/icudata.lst


## Data Files [713]
DATAFILES= CurrencyData.res af.res af_ZA.res am.res am_ET.res ar.res ar_AE.res \
 ar_BH.res ar_DZ.res ar_EG.res ar_IQ.res ar_JO.res ar_KW.res ar_LB.res \
 ar_LY.res ar_MA.res ar_OM.res ar_QA.res ar_SA.res ar_SD.res ar_SY.res \
 ar_TN.res ar_YE.res as.res as_IN.res az.res az_AZ.res az_Cyrl.res az_Cyrl_AZ.res \
 az_Latn.res az_Latn_AZ.res be.res be_BY.res bg.res bg_BG.res bn.res \
 bn_IN.res brkitr/char.brk brkitr/en.res brkitr/en_US.res brkitr/en_US_POSIX.res \
 brkitr/ja.res brkitr/line.brk brkitr/res_index.res brkitr/root.res \
 brkitr/sent.brk brkitr/thaidict.ctd brkitr/title.brk brkitr/word.brk \
 brkitr/word_POSIX.brk brkitr/word_ja.brk ca.res ca_ES.res cns-11643-1992.cnv \
 cnvalias.icu coll/ar.res coll/ar_AE.res coll/ar_BH.res coll/ar_DZ.res \
 coll/ar_EG.res coll/ar_IQ.res coll/ar_JO.res coll/ar_KW.res coll/ar_LB.res \
 coll/ar_LY.res coll/ar_MA.res coll/ar_OM.res coll/ar_QA.res coll/ar_SA.res \
 coll/ar_SD.res coll/ar_SY.res coll/ar_TN.res coll/ar_YE.res coll/as.res \
 coll/as_IN.res coll/be.res coll/be_BY.res coll/bg.res coll/bg_BG.res \
 coll/bn.res coll/ca.res coll/ca_ES.res coll/cs.res coll/cs_CZ.res \
 coll/da.res coll/da_DK.res coll/de.res coll/de_.res coll/de_AT.res \
 coll/de_BE.res coll/de_CH.res coll/de_DE.res coll/de_LU.res coll/de__PHONEBOOK.res \
 coll/el.res coll/el_GR.res coll/en.res coll/en_AU.res coll/en_BE.res \
 coll/en_BW.res coll/en_CA.res coll/en_GB.res coll/en_HK.res coll/en_IE.res \
 coll/en_IN.res coll/en_MT.res coll/en_NZ.res coll/en_PH.res coll/en_SG.res \
 coll/en_US.res coll/en_US_POSIX.res coll/en_VI.res coll/en_ZA.res \
 coll/en_ZW.res coll/eo.res coll/es.res coll/es_.res coll/es_AR.res \
 coll/es_BO.res coll/es_CL.res coll/es_CO.res coll/es_CR.res coll/es_DO.res \
 coll/es_EC.res coll/es_ES.res coll/es_GT.res coll/es_HN.res coll/es_MX.res \
 coll/es_NI.res coll/es_PA.res coll/es_PE.res coll/es_PR.res coll/es_PY.res \
 coll/es_SV.res coll/es_US.res coll/es_UY.res coll/es_VE.res coll/es__TRADITIONAL.res \
 coll/et.res coll/et_EE.res coll/fa.res coll/fa_AF.res coll/fa_IR.res \
 coll/fi.res coll/fi_FI.res coll/fo.res coll/fo_FO.res coll/fr.res \
 coll/fr_BE.res coll/fr_CA.res coll/fr_CH.res coll/fr_FR.res coll/fr_LU.res \
 coll/ga.res coll/ga_IE.res coll/gu.res coll/gu_IN.res coll/haw.res \
 coll/he.res coll/he_IL.res coll/hi.res coll/hi_.res coll/hi_IN.res \
 coll/hi__DIRECT.res coll/hr.res coll/hr_HR.res coll/hu.res coll/hu_HU.res \
 coll/id.res coll/id_ID.res coll/in.res coll/in_ID.res coll/is.res \
 coll/is_IS.res coll/it.res coll/it_CH.res coll/it_IT.res coll/iw.res \
 coll/iw_IL.res coll/ja.res coll/ja_JP.res coll/kk.res coll/kk_KZ.res \
 coll/kl.res coll/kl_GL.res coll/kn.res coll/kn_IN.res coll/ko.res \
 coll/ko_KR.res coll/kok.res coll/lt.res coll/lt_LT.res coll/lv.res \
 coll/lv_LV.res coll/mk.res coll/mk_MK.res coll/ml.res coll/mr.res \
 coll/mr_IN.res coll/ms.res coll/ms_BN.res coll/ms_MY.res coll/mt.res \
 coll/mt_MT.res coll/nb.res coll/nb_NO.res coll/nl.res coll/nl_BE.res \
 coll/nl_NL.res coll/nn.res coll/nn_NO.res coll/om.res coll/om_ET.res \
 coll/om_KE.res coll/or.res coll/pa.res coll/pa_IN.res coll/pl.res \
 coll/pl_PL.res coll/ps.res coll/ps_AF.res coll/pt.res coll/pt_BR.res \
 coll/pt_PT.res coll/res_index.res coll/ro.res coll/ro_RO.res coll/root.res \
 coll/ru.res coll/ru_RU.res coll/ru_UA.res coll/sh.res coll/sh_BA.res \
 coll/sh_YU.res coll/sk.res coll/sk_SK.res coll/sl.res coll/sl_SI.res \
 coll/sq.res coll/sq_AL.res coll/sr.res coll/sr_BA.res coll/sr_Cyrl.res \
 coll/sr_Cyrl_BA.res coll/sr_Cyrl_YU.res coll/sr_YU.res coll/sv.res \
 coll/sv_FI.res coll/sv_SE.res coll/ta.res coll/ta_IN.res coll/te.res \
 coll/te_IN.res coll/th.res coll/th_TH.res coll/tr.res coll/tr_TR.res \
 coll/uk.res coll/uk_UA.res coll/vi.res coll/vi_VN.res coll/zh.res \
 coll/zh_.res coll/zh_CN.res coll/zh_HK.res coll/zh_Hant.res coll/zh_MO.res \
 coll/zh_SG.res coll/zh_TW.res coll/zh_TW_STROKE.res coll/zh__PINYIN.res \
 cs.res cs_CZ.res cy.res cy_GB.res da.res da_DK.res de.res de_AT.res de_BE.res \
 de_CH.res de_DE.res de_LU.res ebcdic-xml-us.cnv el.res el_GR.res en.res \
 en_AU.res en_BE.res en_BW.res en_CA.res en_GB.res en_HK.res en_IE.res \
 en_IN.res en_MT.res en_NZ.res en_PH.res en_PK.res en_RH.res en_SG.res \
 en_US.res en_US_POSIX.res en_VI.res en_ZA.res en_ZW.res eo.res es.res \
 es_AR.res es_BO.res es_CL.res es_CO.res es_CR.res es_DO.res es_EC.res \
 es_ES.res es_GT.res es_HN.res es_MX.res es_NI.res es_PA.res es_PE.res \
 es_PR.res es_PY.res es_SV.res es_US.res es_UY.res es_VE.res et.res et_EE.res \
 eu.res eu_ES.res fa.res fa_AF.res fa_IR.res fi.res fi_FI.res fo.res fo_FO.res \
 fr.res fr_BE.res fr_CA.res fr_CH.res fr_FR.res fr_LU.res ga.res ga_IE.res \
 gb18030.cnv gl.res gl_ES.res gu.res gu_IN.res gv.res gv_GB.res haw.res \
 haw_US.res he.res he_IL.res hi.res hi_IN.res hr.res hr_HR.res hu.res \
 hu_HU.res hy.res hy_AM.res hy_AM_REVISED.res ibm-1006_P100-1995.cnv \
 ibm-1025_P100-1995.cnv ibm-1026_P100-1995.cnv ibm-1047_P100-1995.cnv \
 ibm-1051_P100-1995.cnv ibm-1089_P100-1995.cnv ibm-1097_P100-1995.cnv \
 ibm-1098_P100-1995.cnv ibm-1112_P100-1995.cnv ibm-1122_P100-1999.cnv \
 ibm-1123_P100-1995.cnv ibm-1124_P100-1996.cnv ibm-1125_P100-1997.cnv \
 ibm-1129_P100-1997.cnv ibm-1130_P100-1997.cnv ibm-1131_P100-1997.cnv \
 ibm-1132_P100-1998.cnv ibm-1133_P100-1997.cnv ibm-1137_P100-1999.cnv \
 ibm-1140_P100-1997.cnv ibm-1141_P100-1997.cnv ibm-1142_P100-1997.cnv \
 ibm-1143_P100-1997.cnv ibm-1144_P100-1997.cnv ibm-1145_P100-1997.cnv \
 ibm-1146_P100-1997.cnv ibm-1147_P100-1997.cnv ibm-1148_P100-1997.cnv \
 ibm-1149_P100-1997.cnv ibm-1153_P100-1999.cnv ibm-1154_P100-1999.cnv \
 ibm-1155_P100-1999.cnv ibm-1156_P100-1999.cnv ibm-1157_P100-1999.cnv \
 ibm-1158_P100-1999.cnv ibm-1160_P100-1999.cnv ibm-1162_P100-1999.cnv \
 ibm-1164_P100-1999.cnv ibm-1168_P100-2002.cnv ibm-1250_P100-1995.cnv \
 ibm-1251_P100-1995.cnv ibm-1252_P100-2000.cnv ibm-1253_P100-1995.cnv \
 ibm-1254_P100-1995.cnv ibm-1255_P100-1995.cnv ibm-1256_P110-1997.cnv \
 ibm-1257_P100-1995.cnv ibm-1258_P100-1997.cnv ibm-12712_P100-1998.cnv \
 ibm-1276_P100-1995.cnv ibm-1363_P110-1997.cnv ibm-1363_P11B-1998.cnv \
 ibm-1364_P110-1997.cnv ibm-1371_P100-1999.cnv ibm-1373_P100-2002.cnv \
 ibm-1375_P100-2003.cnv ibm-1383_P110-1999.cnv ibm-1386_P100-2002.cnv \
 ibm-1388_P103-2001.cnv ibm-1390_P110-2003.cnv ibm-1399_P110-2003.cnv \
 ibm-16684_P110-2003.cnv ibm-16804_X110-1999.cnv ibm-273_P100-1995.cnv \
 ibm-277_P100-1995.cnv ibm-278_P100-1995.cnv ibm-280_P100-1995.cnv \
 ibm-284_P100-1995.cnv ibm-285_P100-1995.cnv ibm-290_P100-1995.cnv \
 ibm-297_P100-1995.cnv ibm-33722_P120-1999.cnv ibm-33722_P12A-1999.cnv \
 ibm-367_P100-1995.cnv ibm-37_P100-1995.cnv ibm-420_X120-1999.cnv \
 ibm-424_P100-1995.cnv ibm-437_P100-1995.cnv ibm-4517_P100-2005.cnv \
 ibm-4899_P100-1998.cnv ibm-4909_P100-1999.cnv ibm-4971_P100-1999.cnv \
 ibm-500_P100-1995.cnv ibm-5123_P100-1999.cnv ibm-5346_P100-1998.cnv \
 ibm-5347_P100-1998.cnv ibm-5348_P100-1997.cnv ibm-5349_P100-1998.cnv \
 ibm-5350_P100-1998.cnv ibm-5351_P100-1998.cnv ibm-5352_P100-1998.cnv \
 ibm-5353_P100-1998.cnv ibm-5354_P100-1998.cnv ibm-5478_P100-1995.cnv \
 ibm-737_P100-1997.cnv ibm-775_P100-1996.cnv ibm-803_P100-1999.cnv \
 ibm-813_P100-1995.cnv ibm-838_P100-1995.cnv ibm-8482_P100-1999.cnv \
 ibm-850_P100-1995.cnv ibm-851_P100-1995.cnv ibm-852_P100-1995.cnv \
 ibm-855_P100-1995.cnv ibm-856_P100-1995.cnv ibm-857_P100-1995.cnv \
 ibm-858_P100-1997.cnv ibm-860_P100-1995.cnv ibm-861_P100-1995.cnv \
 ibm-862_P100-1995.cnv ibm-863_P100-1995.cnv ibm-864_X110-1999.cnv \
 ibm-865_P100-1995.cnv ibm-866_P100-1995.cnv ibm-867_P100-1998.cnv \
 ibm-868_P100-1995.cnv ibm-869_P100-1995.cnv ibm-870_P100-1995.cnv \
 ibm-871_P100-1995.cnv ibm-874_P100-1995.cnv ibm-875_P100-1995.cnv \
 ibm-878_P100-1996.cnv ibm-897_P100-1995.cnv ibm-9005_X100-2005.cnv \
 ibm-901_P100-1999.cnv ibm-902_P100-1999.cnv ibm-9067_X100-2005.cnv \
 ibm-912_P100-1995.cnv ibm-913_P100-2000.cnv ibm-914_P100-1995.cnv \
 ibm-915_P100-1995.cnv ibm-916_P100-1995.cnv ibm-918_P100-1995.cnv \
 ibm-920_P100-1995.cnv ibm-921_P100-1995.cnv ibm-922_P100-1999.cnv \
 ibm-923_P100-1998.cnv ibm-930_P120-1999.cnv ibm-933_P110-1995.cnv \
 ibm-935_P110-1999.cnv ibm-937_P110-1999.cnv ibm-939_P120-1999.cnv \
 ibm-942_P12A-1999.cnv ibm-943_P130-1999.cnv ibm-943_P15A-2003.cnv \
 ibm-9447_P100-2002.cnv ibm-9448_X100-2005.cnv ibm-9449_P100-2002.cnv \
 ibm-949_P110-1999.cnv ibm-949_P11A-1999.cnv ibm-950_P110-1999.cnv \
 ibm-954_P101-2000.cnv ibm-964_P110-1999.cnv ibm-970_P110-1995.cnv \
 ibm-971_P100-1995.cnv icu-internal-25546.cnv id.res id_ID.res in.res \
 in_ID.res invuca.icu is.res is_IS.res iso-8859_10-1998.cnv iso-8859_11-2001.cnv \
 iso-8859_14-1998.cnv iso-ir-165.cnv it.res it_CH.res it_IT.res iw.res \
 iw_IL.res ja.res ja_JP.res ja_JP_TRADITIONAL.res jisx-208.cnv jisx-212.cnv \
 kk.res kk_KZ.res kl.res kl_GL.res kn.res kn_IN.res ko.res ko_KR.res kok.res \
 kok_IN.res kw.res kw_GB.res lmb-excp.cnv lt.res lt_LT.res lv.res lv_LV.res \
 macos-0_2-10.2.cnv macos-2566-10.2.cnv macos-29-10.2.cnv macos-35-10.2.cnv \
 macos-6_2-10.4.cnv macos-7_3-10.2.cnv mk.res mk_MK.res ml.res ml_IN.res \
 mr.res mr_IN.res ms.res ms_BN.res ms_MY.res mt.res mt_MT.res nb.res nb_NO.res \
 nl.res nl_BE.res nl_NL.res nn.res nn_NO.res no.res no_NO.res no_NO_NY.res \
 om.res om_ET.res om_KE.res or.res or_IN.res pa.res pa_IN.res pl.res pl_PL.res \
 pnames.icu ps.res ps_AF.res pt.res pt_BR.res pt_PT.res rbnf/da.res rbnf/de.res \
 rbnf/en.res rbnf/en_GB.res rbnf/eo.res rbnf/es.res rbnf/fa.res rbnf/fa_AF.res \
 rbnf/fr.res rbnf/fr_BE.res rbnf/fr_CH.res rbnf/ga.res rbnf/he.res \
 rbnf/it.res rbnf/ja.res rbnf/mt.res rbnf/nl.res rbnf/pl.res rbnf/pt.res \
 rbnf/res_index.res rbnf/root.res rbnf/ru.res rbnf/sv.res rbnf/th.res \
 rbnf/uk.res res_index.res ro.res ro_RO.res root.res ru.res ru_RU.res \
 ru_UA.res sh.res sh_CS.res sh_YU.res sk.res sk_SK.res sl.res sl_SI.res \
 so.res so_DJ.res so_ET.res so_KE.res so_SO.res sq.res sq_AL.res sr.res \
 sr_CS.res sr_Cyrl.res sr_Cyrl_CS.res sr_Cyrl_YU.res sr_Latn.res sr_Latn_CS.res \
 sr_Latn_YU.res sr_YU.res sv.res sv_FI.res sv_SE.res sw.res sw_KE.res \
 sw_TZ.res ta.res ta_IN.res te.res te_IN.res th.res th_TH.res th_TH_TRADITIONAL.res \
 ti.res ti_ER.res ti_ET.res tr.res tr_TR.res translit/el.res translit/en.res \
 translit/root.res ucadata.icu uidna.spp uk.res uk_UA.res unames.icu \
 ur.res ur_IN.res ur_PK.res uz.res uz_Cyrl.res uz_Cyrl_UZ.res uz_Latn.res \
 uz_Latn_UZ.res uz_UZ.res vi.res vi_VN.res windows-874-2000.cnv windows-936-2000.cnv \
 windows-949-2000.cnv windows-950-2000.cnv zh.res zh_CN.res zh_HK.res \
 zh_Hans.res zh_Hans_CN.res zh_Hans_SG.res zh_Hant.res zh_Hant_HK.res \
 zh_Hant_MO.res zh_Hant_TW.res zh_MO.res zh_SG.res zh_TW.res zoneinfo.res


## Data File Paths [713]
DATAFILEPATHS= /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/CurrencyData.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/af.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/af_ZA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/am.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/am_ET.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_AE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_BH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_DZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_EG.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_IQ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_JO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_KW.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_LB.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_LY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_MA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_OM.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_QA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_SA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_SD.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_SY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_TN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ar_YE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/as.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/as_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/az.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/az_AZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/az_Cyrl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/az_Cyrl_AZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/az_Latn.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/az_Latn_AZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/be.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/be_BY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/bg.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/bg_BG.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/bn.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/bn_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/char.brk \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/en.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/en_US.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/en_US_POSIX.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/ja.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/line.brk \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/res_index.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/root.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/sent.brk \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/thaidict.ctd \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/title.brk \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/word.brk \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/word_POSIX.brk \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/brkitr/word_ja.brk \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ca.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ca_ES.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/cns-11643-1992.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/cnvalias.icu \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_AE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_BH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_DZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_EG.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_IQ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_JO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_KW.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_LB.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_LY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_MA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_OM.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_QA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_SA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_SD.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_SY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_TN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ar_YE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/as.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/as_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/be.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/be_BY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/bg.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/bg_BG.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/bn.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ca.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ca_ES.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/cs.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/cs_CZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/da.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/da_DK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/de.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/de_.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/de_AT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/de_BE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/de_CH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/de_DE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/de_LU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/de__PHONEBOOK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/el.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/el_GR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_AU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_BE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_BW.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_CA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_GB.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_HK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_IE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_MT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_NZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_PH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_SG.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_US.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_US_POSIX.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_VI.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_ZA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/en_ZW.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/eo.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_AR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_BO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_CL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_CO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_CR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_DO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_EC.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_ES.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_GT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_HN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_MX.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_NI.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_PA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_PE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_PR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_PY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_SV.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_US.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_UY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es_VE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/es__TRADITIONAL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/et.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/et_EE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fa.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fa_AF.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fa_IR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fi.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fi_FI.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fo.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fo_FO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fr.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fr_BE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fr_CA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fr_CH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fr_FR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/fr_LU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ga.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ga_IE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/gu.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/gu_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/haw.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/he.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/he_IL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/hi.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/hi_.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/hi_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/hi__DIRECT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/hr.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/hr_HR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/hu.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/hu_HU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/id.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/id_ID.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/in.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/in_ID.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/is.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/is_IS.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/it.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/it_CH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/it_IT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/iw.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/iw_IL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ja.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ja_JP.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/kk.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/kk_KZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/kl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/kl_GL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/kn.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/kn_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ko.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ko_KR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/kok.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/lt.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/lt_LT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/lv.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/lv_LV.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/mk.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/mk_MK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ml.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/mr.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/mr_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ms.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ms_BN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ms_MY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/mt.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/mt_MT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/nb.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/nb_NO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/nl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/nl_BE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/nl_NL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/nn.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/nn_NO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/om.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/om_ET.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/om_KE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/or.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/pa.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/pa_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/pl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/pl_PL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ps.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ps_AF.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/pt.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/pt_BR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/pt_PT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/res_index.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ro.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ro_RO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/root.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ru.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ru_RU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ru_UA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sh.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sh_BA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sh_YU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sk.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sk_SK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sl_SI.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sq.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sq_AL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sr.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sr_BA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sr_Cyrl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sr_Cyrl_BA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sr_Cyrl_YU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sr_YU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sv.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sv_FI.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/sv_SE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ta.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/ta_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/te.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/te_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/th.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/th_TH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/tr.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/tr_TR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/uk.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/uk_UA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/vi.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/vi_VN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/zh.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/zh_.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/zh_CN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/zh_HK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/zh_Hant.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/zh_MO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/zh_SG.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/zh_TW.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/zh_TW_STROKE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/coll/zh__PINYIN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/cs.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/cs_CZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/cy.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/cy_GB.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/da.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/da_DK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/de.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/de_AT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/de_BE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/de_CH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/de_DE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/de_LU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ebcdic-xml-us.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/el.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/el_GR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_AU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_BE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_BW.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_CA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_GB.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_HK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_IE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_MT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_NZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_PH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_PK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_RH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_SG.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_US.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_US_POSIX.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_VI.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_ZA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/en_ZW.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/eo.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_AR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_BO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_CL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_CO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_CR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_DO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_EC.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_ES.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_GT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_HN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_MX.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_NI.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_PA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_PE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_PR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_PY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_SV.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_US.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_UY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/es_VE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/et.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/et_EE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/eu.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/eu_ES.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fa.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fa_AF.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fa_IR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fi.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fi_FI.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fo.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fo_FO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fr.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fr_BE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fr_CA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fr_CH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fr_FR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/fr_LU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ga.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ga_IE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/gb18030.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/gl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/gl_ES.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/gu.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/gu_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/gv.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/gv_GB.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/haw.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/haw_US.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/he.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/he_IL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/hi.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/hi_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/hr.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/hr_HR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/hu.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/hu_HU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/hy.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/hy_AM.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/hy_AM_REVISED.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1006_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1025_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1026_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1047_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1051_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1089_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1097_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1098_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1112_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1122_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1123_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1124_P100-1996.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1125_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1129_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1130_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1131_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1132_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1133_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1137_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1140_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1141_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1142_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1143_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1144_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1145_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1146_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1147_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1148_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1149_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1153_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1154_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1155_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1156_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1157_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1158_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1160_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1162_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1164_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1168_P100-2002.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1250_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1251_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1252_P100-2000.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1253_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1254_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1255_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1256_P110-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1257_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1258_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-12712_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1276_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1363_P110-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1363_P11B-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1364_P110-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1371_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1373_P100-2002.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1375_P100-2003.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1383_P110-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1386_P100-2002.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1388_P103-2001.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1390_P110-2003.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-1399_P110-2003.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-16684_P110-2003.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-16804_X110-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-273_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-277_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-278_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-280_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-284_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-285_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-290_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-297_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-33722_P120-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-33722_P12A-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-367_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-37_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-420_X120-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-424_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-437_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-4517_P100-2005.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-4899_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-4909_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-4971_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-500_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-5123_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-5346_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-5347_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-5348_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-5349_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-5350_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-5351_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-5352_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-5353_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-5354_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-5478_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-737_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-775_P100-1996.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-803_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-813_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-838_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-8482_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-850_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-851_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-852_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-855_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-856_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-857_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-858_P100-1997.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-860_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-861_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-862_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-863_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-864_X110-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-865_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-866_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-867_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-868_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-869_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-870_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-871_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-874_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-875_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-878_P100-1996.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-897_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-9005_X100-2005.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-901_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-902_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-9067_X100-2005.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-912_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-913_P100-2000.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-914_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-915_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-916_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-918_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-920_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-921_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-922_P100-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-923_P100-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-930_P120-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-933_P110-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-935_P110-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-937_P110-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-939_P120-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-942_P12A-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-943_P130-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-943_P15A-2003.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-9447_P100-2002.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-9448_X100-2005.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-9449_P100-2002.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-949_P110-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-949_P11A-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-950_P110-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-954_P101-2000.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-964_P110-1999.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-970_P110-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ibm-971_P100-1995.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/icu-internal-25546.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/id.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/id_ID.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/in.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/in_ID.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/invuca.icu \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/is.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/is_IS.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/iso-8859_10-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/iso-8859_11-2001.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/iso-8859_14-1998.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/iso-ir-165.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/it.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/it_CH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/it_IT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/iw.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/iw_IL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ja.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ja_JP.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ja_JP_TRADITIONAL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/jisx-208.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/jisx-212.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/kk.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/kk_KZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/kl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/kl_GL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/kn.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/kn_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ko.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ko_KR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/kok.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/kok_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/kw.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/kw_GB.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/lmb-excp.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/lt.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/lt_LT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/lv.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/lv_LV.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/macos-0_2-10.2.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/macos-2566-10.2.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/macos-29-10.2.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/macos-35-10.2.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/macos-6_2-10.4.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/macos-7_3-10.2.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/mk.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/mk_MK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ml.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ml_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/mr.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/mr_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ms.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ms_BN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ms_MY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/mt.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/mt_MT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/nb.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/nb_NO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/nl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/nl_BE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/nl_NL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/nn.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/nn_NO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/no.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/no_NO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/no_NO_NY.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/om.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/om_ET.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/om_KE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/or.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/or_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/pa.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/pa_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/pl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/pl_PL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/pnames.icu \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ps.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ps_AF.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/pt.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/pt_BR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/pt_PT.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/da.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/de.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/en.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/en_GB.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/eo.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/es.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/fa.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/fa_AF.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/fr.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/fr_BE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/fr_CH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/ga.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/he.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/it.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/ja.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/mt.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/nl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/pl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/pt.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/res_index.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/root.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/ru.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/sv.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/th.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/rbnf/uk.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/res_index.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ro.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ro_RO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/root.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ru.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ru_RU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ru_UA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sh.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sh_CS.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sh_YU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sk.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sk_SK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sl_SI.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/so.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/so_DJ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/so_ET.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/so_KE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/so_SO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sq.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sq_AL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sr.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sr_CS.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sr_Cyrl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sr_Cyrl_CS.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sr_Cyrl_YU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sr_Latn.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sr_Latn_CS.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sr_Latn_YU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sr_YU.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sv.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sv_FI.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sv_SE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sw.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sw_KE.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/sw_TZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ta.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ta_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/te.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/te_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/th.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/th_TH.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/th_TH_TRADITIONAL.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ti.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ti_ER.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ti_ET.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/tr.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/tr_TR.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/translit/el.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/translit/en.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/translit/root.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ucadata.icu \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/uidna.spp \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/uk.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/uk_UA.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/unames.icu \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ur.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ur_IN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/ur_PK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/uz.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/uz_Cyrl.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/uz_Cyrl_UZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/uz_Latn.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/uz_Latn_UZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/uz_UZ.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/vi.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/vi_VN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/windows-874-2000.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/windows-936-2000.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/windows-949-2000.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/windows-950-2000.cnv \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh_CN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh_HK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh_Hans.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh_Hans_CN.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh_Hans_SG.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh_Hant.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh_Hant_HK.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh_Hant_MO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh_Hant_TW.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh_MO.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh_SG.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zh_TW.res \
 /home/tjw/tjKindle/WEBKIT0/icu-3.6/source/data/out/build/icudt36l/zoneinfo.res


# Version numbers:
VERSIONED=.36.0
DLL_LDFLAGS=$(LD_SONAME) $(RPATH_LDFLAGS) $(BIR_LDFLAGS)
DLL_DEPS=$(BIR_DEPS)

# File to make:
TARGET=lib$(LIBNAME).so

SO_TARGET=$(TARGET)
SO_TARGET_VERSION=36.0
SO_TARGET_VERSION_MAJOR=36

DYNAMICCPPFLAGS=$(SHAREDLIBCPPFLAGS)
DYNAMICCFLAGS=$(SHAREDLIBCFLAGS)
DYNAMICCXXFLAGS=$(SHAREDLIBCXXFLAGS)

all: $(TARGETDIR)/$(FINAL_SO_TARGET) $(BATCH_TARGET) $(TARGETDIR)/$(MIDDLE_SO_TARGET) $(TARGETDIR)/$(SO_TARGET)

$(TEMP_PATH)CurrencyData_res.o : $(SRCDIR)/CurrencyData.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/CurrencyData_res.c
	@$(RMV) $(TEMP_DIR)/CurrencyData_res.c

$(TEMP_PATH)af_res.o : $(SRCDIR)/af.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/af_res.c
	@$(RMV) $(TEMP_DIR)/af_res.c

$(TEMP_PATH)af_ZA_res.o : $(SRCDIR)/af_ZA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/af_ZA_res.c
	@$(RMV) $(TEMP_DIR)/af_ZA_res.c

$(TEMP_PATH)am_res.o : $(SRCDIR)/am.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/am_res.c
	@$(RMV) $(TEMP_DIR)/am_res.c

$(TEMP_PATH)am_ET_res.o : $(SRCDIR)/am_ET.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/am_ET_res.c
	@$(RMV) $(TEMP_DIR)/am_ET_res.c

$(TEMP_PATH)ar_res.o : $(SRCDIR)/ar.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_res.c
	@$(RMV) $(TEMP_DIR)/ar_res.c

$(TEMP_PATH)ar_AE_res.o : $(SRCDIR)/ar_AE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_AE_res.c
	@$(RMV) $(TEMP_DIR)/ar_AE_res.c

$(TEMP_PATH)ar_BH_res.o : $(SRCDIR)/ar_BH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_BH_res.c
	@$(RMV) $(TEMP_DIR)/ar_BH_res.c

$(TEMP_PATH)ar_DZ_res.o : $(SRCDIR)/ar_DZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_DZ_res.c
	@$(RMV) $(TEMP_DIR)/ar_DZ_res.c

$(TEMP_PATH)ar_EG_res.o : $(SRCDIR)/ar_EG.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_EG_res.c
	@$(RMV) $(TEMP_DIR)/ar_EG_res.c

$(TEMP_PATH)ar_IQ_res.o : $(SRCDIR)/ar_IQ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_IQ_res.c
	@$(RMV) $(TEMP_DIR)/ar_IQ_res.c

$(TEMP_PATH)ar_JO_res.o : $(SRCDIR)/ar_JO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_JO_res.c
	@$(RMV) $(TEMP_DIR)/ar_JO_res.c

$(TEMP_PATH)ar_KW_res.o : $(SRCDIR)/ar_KW.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_KW_res.c
	@$(RMV) $(TEMP_DIR)/ar_KW_res.c

$(TEMP_PATH)ar_LB_res.o : $(SRCDIR)/ar_LB.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_LB_res.c
	@$(RMV) $(TEMP_DIR)/ar_LB_res.c

$(TEMP_PATH)ar_LY_res.o : $(SRCDIR)/ar_LY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_LY_res.c
	@$(RMV) $(TEMP_DIR)/ar_LY_res.c

$(TEMP_PATH)ar_MA_res.o : $(SRCDIR)/ar_MA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_MA_res.c
	@$(RMV) $(TEMP_DIR)/ar_MA_res.c

$(TEMP_PATH)ar_OM_res.o : $(SRCDIR)/ar_OM.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_OM_res.c
	@$(RMV) $(TEMP_DIR)/ar_OM_res.c

$(TEMP_PATH)ar_QA_res.o : $(SRCDIR)/ar_QA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_QA_res.c
	@$(RMV) $(TEMP_DIR)/ar_QA_res.c

$(TEMP_PATH)ar_SA_res.o : $(SRCDIR)/ar_SA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_SA_res.c
	@$(RMV) $(TEMP_DIR)/ar_SA_res.c

$(TEMP_PATH)ar_SD_res.o : $(SRCDIR)/ar_SD.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_SD_res.c
	@$(RMV) $(TEMP_DIR)/ar_SD_res.c

$(TEMP_PATH)ar_SY_res.o : $(SRCDIR)/ar_SY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_SY_res.c
	@$(RMV) $(TEMP_DIR)/ar_SY_res.c

$(TEMP_PATH)ar_TN_res.o : $(SRCDIR)/ar_TN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_TN_res.c
	@$(RMV) $(TEMP_DIR)/ar_TN_res.c

$(TEMP_PATH)ar_YE_res.o : $(SRCDIR)/ar_YE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ar_YE_res.c
	@$(RMV) $(TEMP_DIR)/ar_YE_res.c

$(TEMP_PATH)as_res.o : $(SRCDIR)/as.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/as_res.c
	@$(RMV) $(TEMP_DIR)/as_res.c

$(TEMP_PATH)as_IN_res.o : $(SRCDIR)/as_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/as_IN_res.c
	@$(RMV) $(TEMP_DIR)/as_IN_res.c

$(TEMP_PATH)az_res.o : $(SRCDIR)/az.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/az_res.c
	@$(RMV) $(TEMP_DIR)/az_res.c

$(TEMP_PATH)az_AZ_res.o : $(SRCDIR)/az_AZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/az_AZ_res.c
	@$(RMV) $(TEMP_DIR)/az_AZ_res.c

$(TEMP_PATH)az_Cyrl_res.o : $(SRCDIR)/az_Cyrl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/az_Cyrl_res.c
	@$(RMV) $(TEMP_DIR)/az_Cyrl_res.c

$(TEMP_PATH)az_Cyrl_AZ_res.o : $(SRCDIR)/az_Cyrl_AZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/az_Cyrl_AZ_res.c
	@$(RMV) $(TEMP_DIR)/az_Cyrl_AZ_res.c

$(TEMP_PATH)az_Latn_res.o : $(SRCDIR)/az_Latn.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/az_Latn_res.c
	@$(RMV) $(TEMP_DIR)/az_Latn_res.c

$(TEMP_PATH)az_Latn_AZ_res.o : $(SRCDIR)/az_Latn_AZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/az_Latn_AZ_res.c
	@$(RMV) $(TEMP_DIR)/az_Latn_AZ_res.c

$(TEMP_PATH)be_res.o : $(SRCDIR)/be.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/be_res.c
	@$(RMV) $(TEMP_DIR)/be_res.c

$(TEMP_PATH)be_BY_res.o : $(SRCDIR)/be_BY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/be_BY_res.c
	@$(RMV) $(TEMP_DIR)/be_BY_res.c

$(TEMP_PATH)bg_res.o : $(SRCDIR)/bg.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/bg_res.c
	@$(RMV) $(TEMP_DIR)/bg_res.c

$(TEMP_PATH)bg_BG_res.o : $(SRCDIR)/bg_BG.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/bg_BG_res.c
	@$(RMV) $(TEMP_DIR)/bg_BG_res.c

$(TEMP_PATH)bn_res.o : $(SRCDIR)/bn.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/bn_res.c
	@$(RMV) $(TEMP_DIR)/bn_res.c

$(TEMP_PATH)bn_IN_res.o : $(SRCDIR)/bn_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/bn_IN_res.c
	@$(RMV) $(TEMP_DIR)/bn_IN_res.c

$(TEMP_PATH)brkitr_char_brk.o : $(SRCDIR)/brkitr/char.brk
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_char_brk
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_char_brk.c
	@$(RMV) $(TEMP_DIR)/brkitr_char_brk.c

$(TEMP_PATH)brkitr_en_res.o : $(SRCDIR)/brkitr/en.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_en_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_en_res.c
	@$(RMV) $(TEMP_DIR)/brkitr_en_res.c

$(TEMP_PATH)brkitr_en_US_res.o : $(SRCDIR)/brkitr/en_US.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_en_US_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_en_US_res.c
	@$(RMV) $(TEMP_DIR)/brkitr_en_US_res.c

$(TEMP_PATH)brkitr_en_US_POSIX_res.o : $(SRCDIR)/brkitr/en_US_POSIX.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_en_US_POSIX_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_en_US_POSIX_res.c
	@$(RMV) $(TEMP_DIR)/brkitr_en_US_POSIX_res.c

$(TEMP_PATH)brkitr_ja_res.o : $(SRCDIR)/brkitr/ja.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_ja_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_ja_res.c
	@$(RMV) $(TEMP_DIR)/brkitr_ja_res.c

$(TEMP_PATH)brkitr_line_brk.o : $(SRCDIR)/brkitr/line.brk
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_line_brk
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_line_brk.c
	@$(RMV) $(TEMP_DIR)/brkitr_line_brk.c

$(TEMP_PATH)brkitr_res_index_res.o : $(SRCDIR)/brkitr/res_index.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_res_index_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_res_index_res.c
	@$(RMV) $(TEMP_DIR)/brkitr_res_index_res.c

$(TEMP_PATH)brkitr_root_res.o : $(SRCDIR)/brkitr/root.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_root_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_root_res.c
	@$(RMV) $(TEMP_DIR)/brkitr_root_res.c

$(TEMP_PATH)brkitr_sent_brk.o : $(SRCDIR)/brkitr/sent.brk
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_sent_brk
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_sent_brk.c
	@$(RMV) $(TEMP_DIR)/brkitr_sent_brk.c

$(TEMP_PATH)brkitr_thaidict_ctd.o : $(SRCDIR)/brkitr/thaidict.ctd
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_thaidict_ctd
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_thaidict_ctd.c
	@$(RMV) $(TEMP_DIR)/brkitr_thaidict_ctd.c

$(TEMP_PATH)brkitr_title_brk.o : $(SRCDIR)/brkitr/title.brk
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_title_brk
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_title_brk.c
	@$(RMV) $(TEMP_DIR)/brkitr_title_brk.c

$(TEMP_PATH)brkitr_word_brk.o : $(SRCDIR)/brkitr/word.brk
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_word_brk
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_word_brk.c
	@$(RMV) $(TEMP_DIR)/brkitr_word_brk.c

$(TEMP_PATH)brkitr_word_POSIX_brk.o : $(SRCDIR)/brkitr/word_POSIX.brk
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_word_POSIX_brk
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_word_POSIX_brk.c
	@$(RMV) $(TEMP_DIR)/brkitr_word_POSIX_brk.c

$(TEMP_PATH)brkitr_word_ja_brk.o : $(SRCDIR)/brkitr/word_ja.brk
	$(INVOKE) $(GENCCODE) -n $(CNAME)_brkitr -d $(TEMP_DIR) $< -f brkitr_word_ja_brk
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/brkitr_word_ja_brk.c
	@$(RMV) $(TEMP_DIR)/brkitr_word_ja_brk.c

$(TEMP_PATH)ca_res.o : $(SRCDIR)/ca.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ca_res.c
	@$(RMV) $(TEMP_DIR)/ca_res.c

$(TEMP_PATH)ca_ES_res.o : $(SRCDIR)/ca_ES.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ca_ES_res.c
	@$(RMV) $(TEMP_DIR)/ca_ES_res.c

$(TEMP_PATH)cns_11643_1992_cnv.o : $(SRCDIR)/cns-11643-1992.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/cns_11643_1992_cnv.c
	@$(RMV) $(TEMP_DIR)/cns_11643_1992_cnv.c

$(TEMP_PATH)cnvalias_icu.o : $(SRCDIR)/cnvalias.icu
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/cnvalias_icu.c
	@$(RMV) $(TEMP_DIR)/cnvalias_icu.c

$(TEMP_PATH)coll_ar_res.o : $(SRCDIR)/coll/ar.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_res.c

$(TEMP_PATH)coll_ar_AE_res.o : $(SRCDIR)/coll/ar_AE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_AE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_AE_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_AE_res.c

$(TEMP_PATH)coll_ar_BH_res.o : $(SRCDIR)/coll/ar_BH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_BH_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_BH_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_BH_res.c

$(TEMP_PATH)coll_ar_DZ_res.o : $(SRCDIR)/coll/ar_DZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_DZ_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_DZ_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_DZ_res.c

$(TEMP_PATH)coll_ar_EG_res.o : $(SRCDIR)/coll/ar_EG.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_EG_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_EG_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_EG_res.c

$(TEMP_PATH)coll_ar_IQ_res.o : $(SRCDIR)/coll/ar_IQ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_IQ_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_IQ_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_IQ_res.c

$(TEMP_PATH)coll_ar_JO_res.o : $(SRCDIR)/coll/ar_JO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_JO_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_JO_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_JO_res.c

$(TEMP_PATH)coll_ar_KW_res.o : $(SRCDIR)/coll/ar_KW.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_KW_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_KW_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_KW_res.c

$(TEMP_PATH)coll_ar_LB_res.o : $(SRCDIR)/coll/ar_LB.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_LB_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_LB_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_LB_res.c

$(TEMP_PATH)coll_ar_LY_res.o : $(SRCDIR)/coll/ar_LY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_LY_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_LY_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_LY_res.c

$(TEMP_PATH)coll_ar_MA_res.o : $(SRCDIR)/coll/ar_MA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_MA_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_MA_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_MA_res.c

$(TEMP_PATH)coll_ar_OM_res.o : $(SRCDIR)/coll/ar_OM.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_OM_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_OM_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_OM_res.c

$(TEMP_PATH)coll_ar_QA_res.o : $(SRCDIR)/coll/ar_QA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_QA_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_QA_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_QA_res.c

$(TEMP_PATH)coll_ar_SA_res.o : $(SRCDIR)/coll/ar_SA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_SA_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_SA_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_SA_res.c

$(TEMP_PATH)coll_ar_SD_res.o : $(SRCDIR)/coll/ar_SD.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_SD_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_SD_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_SD_res.c

$(TEMP_PATH)coll_ar_SY_res.o : $(SRCDIR)/coll/ar_SY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_SY_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_SY_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_SY_res.c

$(TEMP_PATH)coll_ar_TN_res.o : $(SRCDIR)/coll/ar_TN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_TN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_TN_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_TN_res.c

$(TEMP_PATH)coll_ar_YE_res.o : $(SRCDIR)/coll/ar_YE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ar_YE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ar_YE_res.c
	@$(RMV) $(TEMP_DIR)/coll_ar_YE_res.c

$(TEMP_PATH)coll_as_res.o : $(SRCDIR)/coll/as.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_as_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_as_res.c
	@$(RMV) $(TEMP_DIR)/coll_as_res.c

$(TEMP_PATH)coll_as_IN_res.o : $(SRCDIR)/coll/as_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_as_IN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_as_IN_res.c
	@$(RMV) $(TEMP_DIR)/coll_as_IN_res.c

$(TEMP_PATH)coll_be_res.o : $(SRCDIR)/coll/be.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_be_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_be_res.c
	@$(RMV) $(TEMP_DIR)/coll_be_res.c

$(TEMP_PATH)coll_be_BY_res.o : $(SRCDIR)/coll/be_BY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_be_BY_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_be_BY_res.c
	@$(RMV) $(TEMP_DIR)/coll_be_BY_res.c

$(TEMP_PATH)coll_bg_res.o : $(SRCDIR)/coll/bg.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_bg_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_bg_res.c
	@$(RMV) $(TEMP_DIR)/coll_bg_res.c

$(TEMP_PATH)coll_bg_BG_res.o : $(SRCDIR)/coll/bg_BG.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_bg_BG_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_bg_BG_res.c
	@$(RMV) $(TEMP_DIR)/coll_bg_BG_res.c

$(TEMP_PATH)coll_bn_res.o : $(SRCDIR)/coll/bn.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_bn_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_bn_res.c
	@$(RMV) $(TEMP_DIR)/coll_bn_res.c

$(TEMP_PATH)coll_ca_res.o : $(SRCDIR)/coll/ca.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ca_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ca_res.c
	@$(RMV) $(TEMP_DIR)/coll_ca_res.c

$(TEMP_PATH)coll_ca_ES_res.o : $(SRCDIR)/coll/ca_ES.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ca_ES_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ca_ES_res.c
	@$(RMV) $(TEMP_DIR)/coll_ca_ES_res.c

$(TEMP_PATH)coll_cs_res.o : $(SRCDIR)/coll/cs.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_cs_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_cs_res.c
	@$(RMV) $(TEMP_DIR)/coll_cs_res.c

$(TEMP_PATH)coll_cs_CZ_res.o : $(SRCDIR)/coll/cs_CZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_cs_CZ_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_cs_CZ_res.c
	@$(RMV) $(TEMP_DIR)/coll_cs_CZ_res.c

$(TEMP_PATH)coll_da_res.o : $(SRCDIR)/coll/da.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_da_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_da_res.c
	@$(RMV) $(TEMP_DIR)/coll_da_res.c

$(TEMP_PATH)coll_da_DK_res.o : $(SRCDIR)/coll/da_DK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_da_DK_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_da_DK_res.c
	@$(RMV) $(TEMP_DIR)/coll_da_DK_res.c

$(TEMP_PATH)coll_de_res.o : $(SRCDIR)/coll/de.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_de_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_de_res.c
	@$(RMV) $(TEMP_DIR)/coll_de_res.c

$(TEMP_PATH)coll_de__res.o : $(SRCDIR)/coll/de_.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_de__res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_de__res.c
	@$(RMV) $(TEMP_DIR)/coll_de__res.c

$(TEMP_PATH)coll_de_AT_res.o : $(SRCDIR)/coll/de_AT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_de_AT_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_de_AT_res.c
	@$(RMV) $(TEMP_DIR)/coll_de_AT_res.c

$(TEMP_PATH)coll_de_BE_res.o : $(SRCDIR)/coll/de_BE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_de_BE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_de_BE_res.c
	@$(RMV) $(TEMP_DIR)/coll_de_BE_res.c

$(TEMP_PATH)coll_de_CH_res.o : $(SRCDIR)/coll/de_CH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_de_CH_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_de_CH_res.c
	@$(RMV) $(TEMP_DIR)/coll_de_CH_res.c

$(TEMP_PATH)coll_de_DE_res.o : $(SRCDIR)/coll/de_DE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_de_DE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_de_DE_res.c
	@$(RMV) $(TEMP_DIR)/coll_de_DE_res.c

$(TEMP_PATH)coll_de_LU_res.o : $(SRCDIR)/coll/de_LU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_de_LU_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_de_LU_res.c
	@$(RMV) $(TEMP_DIR)/coll_de_LU_res.c

$(TEMP_PATH)coll_de__PHONEBOOK_res.o : $(SRCDIR)/coll/de__PHONEBOOK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_de__PHONEBOOK_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_de__PHONEBOOK_res.c
	@$(RMV) $(TEMP_DIR)/coll_de__PHONEBOOK_res.c

$(TEMP_PATH)coll_el_res.o : $(SRCDIR)/coll/el.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_el_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_el_res.c
	@$(RMV) $(TEMP_DIR)/coll_el_res.c

$(TEMP_PATH)coll_el_GR_res.o : $(SRCDIR)/coll/el_GR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_el_GR_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_el_GR_res.c
	@$(RMV) $(TEMP_DIR)/coll_el_GR_res.c

$(TEMP_PATH)coll_en_res.o : $(SRCDIR)/coll/en.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_res.c

$(TEMP_PATH)coll_en_AU_res.o : $(SRCDIR)/coll/en_AU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_AU_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_AU_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_AU_res.c

$(TEMP_PATH)coll_en_BE_res.o : $(SRCDIR)/coll/en_BE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_BE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_BE_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_BE_res.c

$(TEMP_PATH)coll_en_BW_res.o : $(SRCDIR)/coll/en_BW.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_BW_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_BW_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_BW_res.c

$(TEMP_PATH)coll_en_CA_res.o : $(SRCDIR)/coll/en_CA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_CA_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_CA_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_CA_res.c

$(TEMP_PATH)coll_en_GB_res.o : $(SRCDIR)/coll/en_GB.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_GB_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_GB_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_GB_res.c

$(TEMP_PATH)coll_en_HK_res.o : $(SRCDIR)/coll/en_HK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_HK_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_HK_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_HK_res.c

$(TEMP_PATH)coll_en_IE_res.o : $(SRCDIR)/coll/en_IE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_IE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_IE_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_IE_res.c

$(TEMP_PATH)coll_en_IN_res.o : $(SRCDIR)/coll/en_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_IN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_IN_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_IN_res.c

$(TEMP_PATH)coll_en_MT_res.o : $(SRCDIR)/coll/en_MT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_MT_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_MT_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_MT_res.c

$(TEMP_PATH)coll_en_NZ_res.o : $(SRCDIR)/coll/en_NZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_NZ_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_NZ_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_NZ_res.c

$(TEMP_PATH)coll_en_PH_res.o : $(SRCDIR)/coll/en_PH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_PH_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_PH_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_PH_res.c

$(TEMP_PATH)coll_en_SG_res.o : $(SRCDIR)/coll/en_SG.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_SG_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_SG_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_SG_res.c

$(TEMP_PATH)coll_en_US_res.o : $(SRCDIR)/coll/en_US.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_US_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_US_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_US_res.c

$(TEMP_PATH)coll_en_US_POSIX_res.o : $(SRCDIR)/coll/en_US_POSIX.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_US_POSIX_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_US_POSIX_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_US_POSIX_res.c

$(TEMP_PATH)coll_en_VI_res.o : $(SRCDIR)/coll/en_VI.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_VI_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_VI_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_VI_res.c

$(TEMP_PATH)coll_en_ZA_res.o : $(SRCDIR)/coll/en_ZA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_ZA_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_ZA_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_ZA_res.c

$(TEMP_PATH)coll_en_ZW_res.o : $(SRCDIR)/coll/en_ZW.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_en_ZW_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_en_ZW_res.c
	@$(RMV) $(TEMP_DIR)/coll_en_ZW_res.c

$(TEMP_PATH)coll_eo_res.o : $(SRCDIR)/coll/eo.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_eo_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_eo_res.c
	@$(RMV) $(TEMP_DIR)/coll_eo_res.c

$(TEMP_PATH)coll_es_res.o : $(SRCDIR)/coll/es.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_res.c

$(TEMP_PATH)coll_es__res.o : $(SRCDIR)/coll/es_.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es__res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es__res.c
	@$(RMV) $(TEMP_DIR)/coll_es__res.c

$(TEMP_PATH)coll_es_AR_res.o : $(SRCDIR)/coll/es_AR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_AR_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_AR_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_AR_res.c

$(TEMP_PATH)coll_es_BO_res.o : $(SRCDIR)/coll/es_BO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_BO_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_BO_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_BO_res.c

$(TEMP_PATH)coll_es_CL_res.o : $(SRCDIR)/coll/es_CL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_CL_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_CL_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_CL_res.c

$(TEMP_PATH)coll_es_CO_res.o : $(SRCDIR)/coll/es_CO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_CO_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_CO_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_CO_res.c

$(TEMP_PATH)coll_es_CR_res.o : $(SRCDIR)/coll/es_CR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_CR_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_CR_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_CR_res.c

$(TEMP_PATH)coll_es_DO_res.o : $(SRCDIR)/coll/es_DO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_DO_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_DO_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_DO_res.c

$(TEMP_PATH)coll_es_EC_res.o : $(SRCDIR)/coll/es_EC.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_EC_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_EC_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_EC_res.c

$(TEMP_PATH)coll_es_ES_res.o : $(SRCDIR)/coll/es_ES.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_ES_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_ES_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_ES_res.c

$(TEMP_PATH)coll_es_GT_res.o : $(SRCDIR)/coll/es_GT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_GT_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_GT_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_GT_res.c

$(TEMP_PATH)coll_es_HN_res.o : $(SRCDIR)/coll/es_HN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_HN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_HN_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_HN_res.c

$(TEMP_PATH)coll_es_MX_res.o : $(SRCDIR)/coll/es_MX.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_MX_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_MX_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_MX_res.c

$(TEMP_PATH)coll_es_NI_res.o : $(SRCDIR)/coll/es_NI.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_NI_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_NI_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_NI_res.c

$(TEMP_PATH)coll_es_PA_res.o : $(SRCDIR)/coll/es_PA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_PA_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_PA_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_PA_res.c

$(TEMP_PATH)coll_es_PE_res.o : $(SRCDIR)/coll/es_PE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_PE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_PE_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_PE_res.c

$(TEMP_PATH)coll_es_PR_res.o : $(SRCDIR)/coll/es_PR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_PR_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_PR_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_PR_res.c

$(TEMP_PATH)coll_es_PY_res.o : $(SRCDIR)/coll/es_PY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_PY_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_PY_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_PY_res.c

$(TEMP_PATH)coll_es_SV_res.o : $(SRCDIR)/coll/es_SV.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_SV_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_SV_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_SV_res.c

$(TEMP_PATH)coll_es_US_res.o : $(SRCDIR)/coll/es_US.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_US_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_US_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_US_res.c

$(TEMP_PATH)coll_es_UY_res.o : $(SRCDIR)/coll/es_UY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_UY_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_UY_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_UY_res.c

$(TEMP_PATH)coll_es_VE_res.o : $(SRCDIR)/coll/es_VE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es_VE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es_VE_res.c
	@$(RMV) $(TEMP_DIR)/coll_es_VE_res.c

$(TEMP_PATH)coll_es__TRADITIONAL_res.o : $(SRCDIR)/coll/es__TRADITIONAL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_es__TRADITIONAL_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_es__TRADITIONAL_res.c
	@$(RMV) $(TEMP_DIR)/coll_es__TRADITIONAL_res.c

$(TEMP_PATH)coll_et_res.o : $(SRCDIR)/coll/et.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_et_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_et_res.c
	@$(RMV) $(TEMP_DIR)/coll_et_res.c

$(TEMP_PATH)coll_et_EE_res.o : $(SRCDIR)/coll/et_EE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_et_EE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_et_EE_res.c
	@$(RMV) $(TEMP_DIR)/coll_et_EE_res.c

$(TEMP_PATH)coll_fa_res.o : $(SRCDIR)/coll/fa.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fa_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fa_res.c
	@$(RMV) $(TEMP_DIR)/coll_fa_res.c

$(TEMP_PATH)coll_fa_AF_res.o : $(SRCDIR)/coll/fa_AF.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fa_AF_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fa_AF_res.c
	@$(RMV) $(TEMP_DIR)/coll_fa_AF_res.c

$(TEMP_PATH)coll_fa_IR_res.o : $(SRCDIR)/coll/fa_IR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fa_IR_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fa_IR_res.c
	@$(RMV) $(TEMP_DIR)/coll_fa_IR_res.c

$(TEMP_PATH)coll_fi_res.o : $(SRCDIR)/coll/fi.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fi_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fi_res.c
	@$(RMV) $(TEMP_DIR)/coll_fi_res.c

$(TEMP_PATH)coll_fi_FI_res.o : $(SRCDIR)/coll/fi_FI.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fi_FI_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fi_FI_res.c
	@$(RMV) $(TEMP_DIR)/coll_fi_FI_res.c

$(TEMP_PATH)coll_fo_res.o : $(SRCDIR)/coll/fo.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fo_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fo_res.c
	@$(RMV) $(TEMP_DIR)/coll_fo_res.c

$(TEMP_PATH)coll_fo_FO_res.o : $(SRCDIR)/coll/fo_FO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fo_FO_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fo_FO_res.c
	@$(RMV) $(TEMP_DIR)/coll_fo_FO_res.c

$(TEMP_PATH)coll_fr_res.o : $(SRCDIR)/coll/fr.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fr_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fr_res.c
	@$(RMV) $(TEMP_DIR)/coll_fr_res.c

$(TEMP_PATH)coll_fr_BE_res.o : $(SRCDIR)/coll/fr_BE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fr_BE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fr_BE_res.c
	@$(RMV) $(TEMP_DIR)/coll_fr_BE_res.c

$(TEMP_PATH)coll_fr_CA_res.o : $(SRCDIR)/coll/fr_CA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fr_CA_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fr_CA_res.c
	@$(RMV) $(TEMP_DIR)/coll_fr_CA_res.c

$(TEMP_PATH)coll_fr_CH_res.o : $(SRCDIR)/coll/fr_CH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fr_CH_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fr_CH_res.c
	@$(RMV) $(TEMP_DIR)/coll_fr_CH_res.c

$(TEMP_PATH)coll_fr_FR_res.o : $(SRCDIR)/coll/fr_FR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fr_FR_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fr_FR_res.c
	@$(RMV) $(TEMP_DIR)/coll_fr_FR_res.c

$(TEMP_PATH)coll_fr_LU_res.o : $(SRCDIR)/coll/fr_LU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_fr_LU_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_fr_LU_res.c
	@$(RMV) $(TEMP_DIR)/coll_fr_LU_res.c

$(TEMP_PATH)coll_ga_res.o : $(SRCDIR)/coll/ga.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ga_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ga_res.c
	@$(RMV) $(TEMP_DIR)/coll_ga_res.c

$(TEMP_PATH)coll_ga_IE_res.o : $(SRCDIR)/coll/ga_IE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ga_IE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ga_IE_res.c
	@$(RMV) $(TEMP_DIR)/coll_ga_IE_res.c

$(TEMP_PATH)coll_gu_res.o : $(SRCDIR)/coll/gu.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_gu_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_gu_res.c
	@$(RMV) $(TEMP_DIR)/coll_gu_res.c

$(TEMP_PATH)coll_gu_IN_res.o : $(SRCDIR)/coll/gu_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_gu_IN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_gu_IN_res.c
	@$(RMV) $(TEMP_DIR)/coll_gu_IN_res.c

$(TEMP_PATH)coll_haw_res.o : $(SRCDIR)/coll/haw.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_haw_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_haw_res.c
	@$(RMV) $(TEMP_DIR)/coll_haw_res.c

$(TEMP_PATH)coll_he_res.o : $(SRCDIR)/coll/he.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_he_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_he_res.c
	@$(RMV) $(TEMP_DIR)/coll_he_res.c

$(TEMP_PATH)coll_he_IL_res.o : $(SRCDIR)/coll/he_IL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_he_IL_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_he_IL_res.c
	@$(RMV) $(TEMP_DIR)/coll_he_IL_res.c

$(TEMP_PATH)coll_hi_res.o : $(SRCDIR)/coll/hi.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_hi_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_hi_res.c
	@$(RMV) $(TEMP_DIR)/coll_hi_res.c

$(TEMP_PATH)coll_hi__res.o : $(SRCDIR)/coll/hi_.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_hi__res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_hi__res.c
	@$(RMV) $(TEMP_DIR)/coll_hi__res.c

$(TEMP_PATH)coll_hi_IN_res.o : $(SRCDIR)/coll/hi_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_hi_IN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_hi_IN_res.c
	@$(RMV) $(TEMP_DIR)/coll_hi_IN_res.c

$(TEMP_PATH)coll_hi__DIRECT_res.o : $(SRCDIR)/coll/hi__DIRECT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_hi__DIRECT_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_hi__DIRECT_res.c
	@$(RMV) $(TEMP_DIR)/coll_hi__DIRECT_res.c

$(TEMP_PATH)coll_hr_res.o : $(SRCDIR)/coll/hr.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_hr_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_hr_res.c
	@$(RMV) $(TEMP_DIR)/coll_hr_res.c

$(TEMP_PATH)coll_hr_HR_res.o : $(SRCDIR)/coll/hr_HR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_hr_HR_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_hr_HR_res.c
	@$(RMV) $(TEMP_DIR)/coll_hr_HR_res.c

$(TEMP_PATH)coll_hu_res.o : $(SRCDIR)/coll/hu.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_hu_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_hu_res.c
	@$(RMV) $(TEMP_DIR)/coll_hu_res.c

$(TEMP_PATH)coll_hu_HU_res.o : $(SRCDIR)/coll/hu_HU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_hu_HU_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_hu_HU_res.c
	@$(RMV) $(TEMP_DIR)/coll_hu_HU_res.c

$(TEMP_PATH)coll_id_res.o : $(SRCDIR)/coll/id.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_id_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_id_res.c
	@$(RMV) $(TEMP_DIR)/coll_id_res.c

$(TEMP_PATH)coll_id_ID_res.o : $(SRCDIR)/coll/id_ID.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_id_ID_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_id_ID_res.c
	@$(RMV) $(TEMP_DIR)/coll_id_ID_res.c

$(TEMP_PATH)coll_in_res.o : $(SRCDIR)/coll/in.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_in_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_in_res.c
	@$(RMV) $(TEMP_DIR)/coll_in_res.c

$(TEMP_PATH)coll_in_ID_res.o : $(SRCDIR)/coll/in_ID.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_in_ID_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_in_ID_res.c
	@$(RMV) $(TEMP_DIR)/coll_in_ID_res.c

$(TEMP_PATH)coll_is_res.o : $(SRCDIR)/coll/is.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_is_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_is_res.c
	@$(RMV) $(TEMP_DIR)/coll_is_res.c

$(TEMP_PATH)coll_is_IS_res.o : $(SRCDIR)/coll/is_IS.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_is_IS_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_is_IS_res.c
	@$(RMV) $(TEMP_DIR)/coll_is_IS_res.c

$(TEMP_PATH)coll_it_res.o : $(SRCDIR)/coll/it.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_it_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_it_res.c
	@$(RMV) $(TEMP_DIR)/coll_it_res.c

$(TEMP_PATH)coll_it_CH_res.o : $(SRCDIR)/coll/it_CH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_it_CH_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_it_CH_res.c
	@$(RMV) $(TEMP_DIR)/coll_it_CH_res.c

$(TEMP_PATH)coll_it_IT_res.o : $(SRCDIR)/coll/it_IT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_it_IT_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_it_IT_res.c
	@$(RMV) $(TEMP_DIR)/coll_it_IT_res.c

$(TEMP_PATH)coll_iw_res.o : $(SRCDIR)/coll/iw.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_iw_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_iw_res.c
	@$(RMV) $(TEMP_DIR)/coll_iw_res.c

$(TEMP_PATH)coll_iw_IL_res.o : $(SRCDIR)/coll/iw_IL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_iw_IL_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_iw_IL_res.c
	@$(RMV) $(TEMP_DIR)/coll_iw_IL_res.c

$(TEMP_PATH)coll_ja_res.o : $(SRCDIR)/coll/ja.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ja_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ja_res.c
	@$(RMV) $(TEMP_DIR)/coll_ja_res.c

$(TEMP_PATH)coll_ja_JP_res.o : $(SRCDIR)/coll/ja_JP.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ja_JP_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ja_JP_res.c
	@$(RMV) $(TEMP_DIR)/coll_ja_JP_res.c

$(TEMP_PATH)coll_kk_res.o : $(SRCDIR)/coll/kk.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_kk_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_kk_res.c
	@$(RMV) $(TEMP_DIR)/coll_kk_res.c

$(TEMP_PATH)coll_kk_KZ_res.o : $(SRCDIR)/coll/kk_KZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_kk_KZ_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_kk_KZ_res.c
	@$(RMV) $(TEMP_DIR)/coll_kk_KZ_res.c

$(TEMP_PATH)coll_kl_res.o : $(SRCDIR)/coll/kl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_kl_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_kl_res.c
	@$(RMV) $(TEMP_DIR)/coll_kl_res.c

$(TEMP_PATH)coll_kl_GL_res.o : $(SRCDIR)/coll/kl_GL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_kl_GL_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_kl_GL_res.c
	@$(RMV) $(TEMP_DIR)/coll_kl_GL_res.c

$(TEMP_PATH)coll_kn_res.o : $(SRCDIR)/coll/kn.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_kn_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_kn_res.c
	@$(RMV) $(TEMP_DIR)/coll_kn_res.c

$(TEMP_PATH)coll_kn_IN_res.o : $(SRCDIR)/coll/kn_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_kn_IN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_kn_IN_res.c
	@$(RMV) $(TEMP_DIR)/coll_kn_IN_res.c

$(TEMP_PATH)coll_ko_res.o : $(SRCDIR)/coll/ko.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ko_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ko_res.c
	@$(RMV) $(TEMP_DIR)/coll_ko_res.c

$(TEMP_PATH)coll_ko_KR_res.o : $(SRCDIR)/coll/ko_KR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ko_KR_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ko_KR_res.c
	@$(RMV) $(TEMP_DIR)/coll_ko_KR_res.c

$(TEMP_PATH)coll_kok_res.o : $(SRCDIR)/coll/kok.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_kok_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_kok_res.c
	@$(RMV) $(TEMP_DIR)/coll_kok_res.c

$(TEMP_PATH)coll_lt_res.o : $(SRCDIR)/coll/lt.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_lt_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_lt_res.c
	@$(RMV) $(TEMP_DIR)/coll_lt_res.c

$(TEMP_PATH)coll_lt_LT_res.o : $(SRCDIR)/coll/lt_LT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_lt_LT_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_lt_LT_res.c
	@$(RMV) $(TEMP_DIR)/coll_lt_LT_res.c

$(TEMP_PATH)coll_lv_res.o : $(SRCDIR)/coll/lv.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_lv_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_lv_res.c
	@$(RMV) $(TEMP_DIR)/coll_lv_res.c

$(TEMP_PATH)coll_lv_LV_res.o : $(SRCDIR)/coll/lv_LV.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_lv_LV_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_lv_LV_res.c
	@$(RMV) $(TEMP_DIR)/coll_lv_LV_res.c

$(TEMP_PATH)coll_mk_res.o : $(SRCDIR)/coll/mk.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_mk_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_mk_res.c
	@$(RMV) $(TEMP_DIR)/coll_mk_res.c

$(TEMP_PATH)coll_mk_MK_res.o : $(SRCDIR)/coll/mk_MK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_mk_MK_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_mk_MK_res.c
	@$(RMV) $(TEMP_DIR)/coll_mk_MK_res.c

$(TEMP_PATH)coll_ml_res.o : $(SRCDIR)/coll/ml.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ml_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ml_res.c
	@$(RMV) $(TEMP_DIR)/coll_ml_res.c

$(TEMP_PATH)coll_mr_res.o : $(SRCDIR)/coll/mr.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_mr_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_mr_res.c
	@$(RMV) $(TEMP_DIR)/coll_mr_res.c

$(TEMP_PATH)coll_mr_IN_res.o : $(SRCDIR)/coll/mr_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_mr_IN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_mr_IN_res.c
	@$(RMV) $(TEMP_DIR)/coll_mr_IN_res.c

$(TEMP_PATH)coll_ms_res.o : $(SRCDIR)/coll/ms.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ms_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ms_res.c
	@$(RMV) $(TEMP_DIR)/coll_ms_res.c

$(TEMP_PATH)coll_ms_BN_res.o : $(SRCDIR)/coll/ms_BN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ms_BN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ms_BN_res.c
	@$(RMV) $(TEMP_DIR)/coll_ms_BN_res.c

$(TEMP_PATH)coll_ms_MY_res.o : $(SRCDIR)/coll/ms_MY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ms_MY_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ms_MY_res.c
	@$(RMV) $(TEMP_DIR)/coll_ms_MY_res.c

$(TEMP_PATH)coll_mt_res.o : $(SRCDIR)/coll/mt.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_mt_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_mt_res.c
	@$(RMV) $(TEMP_DIR)/coll_mt_res.c

$(TEMP_PATH)coll_mt_MT_res.o : $(SRCDIR)/coll/mt_MT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_mt_MT_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_mt_MT_res.c
	@$(RMV) $(TEMP_DIR)/coll_mt_MT_res.c

$(TEMP_PATH)coll_nb_res.o : $(SRCDIR)/coll/nb.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_nb_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_nb_res.c
	@$(RMV) $(TEMP_DIR)/coll_nb_res.c

$(TEMP_PATH)coll_nb_NO_res.o : $(SRCDIR)/coll/nb_NO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_nb_NO_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_nb_NO_res.c
	@$(RMV) $(TEMP_DIR)/coll_nb_NO_res.c

$(TEMP_PATH)coll_nl_res.o : $(SRCDIR)/coll/nl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_nl_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_nl_res.c
	@$(RMV) $(TEMP_DIR)/coll_nl_res.c

$(TEMP_PATH)coll_nl_BE_res.o : $(SRCDIR)/coll/nl_BE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_nl_BE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_nl_BE_res.c
	@$(RMV) $(TEMP_DIR)/coll_nl_BE_res.c

$(TEMP_PATH)coll_nl_NL_res.o : $(SRCDIR)/coll/nl_NL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_nl_NL_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_nl_NL_res.c
	@$(RMV) $(TEMP_DIR)/coll_nl_NL_res.c

$(TEMP_PATH)coll_nn_res.o : $(SRCDIR)/coll/nn.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_nn_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_nn_res.c
	@$(RMV) $(TEMP_DIR)/coll_nn_res.c

$(TEMP_PATH)coll_nn_NO_res.o : $(SRCDIR)/coll/nn_NO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_nn_NO_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_nn_NO_res.c
	@$(RMV) $(TEMP_DIR)/coll_nn_NO_res.c

$(TEMP_PATH)coll_om_res.o : $(SRCDIR)/coll/om.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_om_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_om_res.c
	@$(RMV) $(TEMP_DIR)/coll_om_res.c

$(TEMP_PATH)coll_om_ET_res.o : $(SRCDIR)/coll/om_ET.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_om_ET_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_om_ET_res.c
	@$(RMV) $(TEMP_DIR)/coll_om_ET_res.c

$(TEMP_PATH)coll_om_KE_res.o : $(SRCDIR)/coll/om_KE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_om_KE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_om_KE_res.c
	@$(RMV) $(TEMP_DIR)/coll_om_KE_res.c

$(TEMP_PATH)coll_or_res.o : $(SRCDIR)/coll/or.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_or_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_or_res.c
	@$(RMV) $(TEMP_DIR)/coll_or_res.c

$(TEMP_PATH)coll_pa_res.o : $(SRCDIR)/coll/pa.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_pa_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_pa_res.c
	@$(RMV) $(TEMP_DIR)/coll_pa_res.c

$(TEMP_PATH)coll_pa_IN_res.o : $(SRCDIR)/coll/pa_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_pa_IN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_pa_IN_res.c
	@$(RMV) $(TEMP_DIR)/coll_pa_IN_res.c

$(TEMP_PATH)coll_pl_res.o : $(SRCDIR)/coll/pl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_pl_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_pl_res.c
	@$(RMV) $(TEMP_DIR)/coll_pl_res.c

$(TEMP_PATH)coll_pl_PL_res.o : $(SRCDIR)/coll/pl_PL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_pl_PL_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_pl_PL_res.c
	@$(RMV) $(TEMP_DIR)/coll_pl_PL_res.c

$(TEMP_PATH)coll_ps_res.o : $(SRCDIR)/coll/ps.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ps_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ps_res.c
	@$(RMV) $(TEMP_DIR)/coll_ps_res.c

$(TEMP_PATH)coll_ps_AF_res.o : $(SRCDIR)/coll/ps_AF.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ps_AF_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ps_AF_res.c
	@$(RMV) $(TEMP_DIR)/coll_ps_AF_res.c

$(TEMP_PATH)coll_pt_res.o : $(SRCDIR)/coll/pt.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_pt_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_pt_res.c
	@$(RMV) $(TEMP_DIR)/coll_pt_res.c

$(TEMP_PATH)coll_pt_BR_res.o : $(SRCDIR)/coll/pt_BR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_pt_BR_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_pt_BR_res.c
	@$(RMV) $(TEMP_DIR)/coll_pt_BR_res.c

$(TEMP_PATH)coll_pt_PT_res.o : $(SRCDIR)/coll/pt_PT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_pt_PT_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_pt_PT_res.c
	@$(RMV) $(TEMP_DIR)/coll_pt_PT_res.c

$(TEMP_PATH)coll_res_index_res.o : $(SRCDIR)/coll/res_index.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_res_index_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_res_index_res.c
	@$(RMV) $(TEMP_DIR)/coll_res_index_res.c

$(TEMP_PATH)coll_ro_res.o : $(SRCDIR)/coll/ro.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ro_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ro_res.c
	@$(RMV) $(TEMP_DIR)/coll_ro_res.c

$(TEMP_PATH)coll_ro_RO_res.o : $(SRCDIR)/coll/ro_RO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ro_RO_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ro_RO_res.c
	@$(RMV) $(TEMP_DIR)/coll_ro_RO_res.c

$(TEMP_PATH)coll_root_res.o : $(SRCDIR)/coll/root.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_root_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_root_res.c
	@$(RMV) $(TEMP_DIR)/coll_root_res.c

$(TEMP_PATH)coll_ru_res.o : $(SRCDIR)/coll/ru.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ru_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ru_res.c
	@$(RMV) $(TEMP_DIR)/coll_ru_res.c

$(TEMP_PATH)coll_ru_RU_res.o : $(SRCDIR)/coll/ru_RU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ru_RU_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ru_RU_res.c
	@$(RMV) $(TEMP_DIR)/coll_ru_RU_res.c

$(TEMP_PATH)coll_ru_UA_res.o : $(SRCDIR)/coll/ru_UA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ru_UA_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ru_UA_res.c
	@$(RMV) $(TEMP_DIR)/coll_ru_UA_res.c

$(TEMP_PATH)coll_sh_res.o : $(SRCDIR)/coll/sh.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sh_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sh_res.c
	@$(RMV) $(TEMP_DIR)/coll_sh_res.c

$(TEMP_PATH)coll_sh_BA_res.o : $(SRCDIR)/coll/sh_BA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sh_BA_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sh_BA_res.c
	@$(RMV) $(TEMP_DIR)/coll_sh_BA_res.c

$(TEMP_PATH)coll_sh_YU_res.o : $(SRCDIR)/coll/sh_YU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sh_YU_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sh_YU_res.c
	@$(RMV) $(TEMP_DIR)/coll_sh_YU_res.c

$(TEMP_PATH)coll_sk_res.o : $(SRCDIR)/coll/sk.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sk_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sk_res.c
	@$(RMV) $(TEMP_DIR)/coll_sk_res.c

$(TEMP_PATH)coll_sk_SK_res.o : $(SRCDIR)/coll/sk_SK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sk_SK_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sk_SK_res.c
	@$(RMV) $(TEMP_DIR)/coll_sk_SK_res.c

$(TEMP_PATH)coll_sl_res.o : $(SRCDIR)/coll/sl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sl_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sl_res.c
	@$(RMV) $(TEMP_DIR)/coll_sl_res.c

$(TEMP_PATH)coll_sl_SI_res.o : $(SRCDIR)/coll/sl_SI.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sl_SI_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sl_SI_res.c
	@$(RMV) $(TEMP_DIR)/coll_sl_SI_res.c

$(TEMP_PATH)coll_sq_res.o : $(SRCDIR)/coll/sq.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sq_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sq_res.c
	@$(RMV) $(TEMP_DIR)/coll_sq_res.c

$(TEMP_PATH)coll_sq_AL_res.o : $(SRCDIR)/coll/sq_AL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sq_AL_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sq_AL_res.c
	@$(RMV) $(TEMP_DIR)/coll_sq_AL_res.c

$(TEMP_PATH)coll_sr_res.o : $(SRCDIR)/coll/sr.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sr_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sr_res.c
	@$(RMV) $(TEMP_DIR)/coll_sr_res.c

$(TEMP_PATH)coll_sr_BA_res.o : $(SRCDIR)/coll/sr_BA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sr_BA_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sr_BA_res.c
	@$(RMV) $(TEMP_DIR)/coll_sr_BA_res.c

$(TEMP_PATH)coll_sr_Cyrl_res.o : $(SRCDIR)/coll/sr_Cyrl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sr_Cyrl_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sr_Cyrl_res.c
	@$(RMV) $(TEMP_DIR)/coll_sr_Cyrl_res.c

$(TEMP_PATH)coll_sr_Cyrl_BA_res.o : $(SRCDIR)/coll/sr_Cyrl_BA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sr_Cyrl_BA_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sr_Cyrl_BA_res.c
	@$(RMV) $(TEMP_DIR)/coll_sr_Cyrl_BA_res.c

$(TEMP_PATH)coll_sr_Cyrl_YU_res.o : $(SRCDIR)/coll/sr_Cyrl_YU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sr_Cyrl_YU_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sr_Cyrl_YU_res.c
	@$(RMV) $(TEMP_DIR)/coll_sr_Cyrl_YU_res.c

$(TEMP_PATH)coll_sr_YU_res.o : $(SRCDIR)/coll/sr_YU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sr_YU_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sr_YU_res.c
	@$(RMV) $(TEMP_DIR)/coll_sr_YU_res.c

$(TEMP_PATH)coll_sv_res.o : $(SRCDIR)/coll/sv.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sv_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sv_res.c
	@$(RMV) $(TEMP_DIR)/coll_sv_res.c

$(TEMP_PATH)coll_sv_FI_res.o : $(SRCDIR)/coll/sv_FI.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sv_FI_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sv_FI_res.c
	@$(RMV) $(TEMP_DIR)/coll_sv_FI_res.c

$(TEMP_PATH)coll_sv_SE_res.o : $(SRCDIR)/coll/sv_SE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_sv_SE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_sv_SE_res.c
	@$(RMV) $(TEMP_DIR)/coll_sv_SE_res.c

$(TEMP_PATH)coll_ta_res.o : $(SRCDIR)/coll/ta.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ta_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ta_res.c
	@$(RMV) $(TEMP_DIR)/coll_ta_res.c

$(TEMP_PATH)coll_ta_IN_res.o : $(SRCDIR)/coll/ta_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_ta_IN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_ta_IN_res.c
	@$(RMV) $(TEMP_DIR)/coll_ta_IN_res.c

$(TEMP_PATH)coll_te_res.o : $(SRCDIR)/coll/te.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_te_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_te_res.c
	@$(RMV) $(TEMP_DIR)/coll_te_res.c

$(TEMP_PATH)coll_te_IN_res.o : $(SRCDIR)/coll/te_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_te_IN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_te_IN_res.c
	@$(RMV) $(TEMP_DIR)/coll_te_IN_res.c

$(TEMP_PATH)coll_th_res.o : $(SRCDIR)/coll/th.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_th_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_th_res.c
	@$(RMV) $(TEMP_DIR)/coll_th_res.c

$(TEMP_PATH)coll_th_TH_res.o : $(SRCDIR)/coll/th_TH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_th_TH_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_th_TH_res.c
	@$(RMV) $(TEMP_DIR)/coll_th_TH_res.c

$(TEMP_PATH)coll_tr_res.o : $(SRCDIR)/coll/tr.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_tr_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_tr_res.c
	@$(RMV) $(TEMP_DIR)/coll_tr_res.c

$(TEMP_PATH)coll_tr_TR_res.o : $(SRCDIR)/coll/tr_TR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_tr_TR_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_tr_TR_res.c
	@$(RMV) $(TEMP_DIR)/coll_tr_TR_res.c

$(TEMP_PATH)coll_uk_res.o : $(SRCDIR)/coll/uk.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_uk_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_uk_res.c
	@$(RMV) $(TEMP_DIR)/coll_uk_res.c

$(TEMP_PATH)coll_uk_UA_res.o : $(SRCDIR)/coll/uk_UA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_uk_UA_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_uk_UA_res.c
	@$(RMV) $(TEMP_DIR)/coll_uk_UA_res.c

$(TEMP_PATH)coll_vi_res.o : $(SRCDIR)/coll/vi.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_vi_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_vi_res.c
	@$(RMV) $(TEMP_DIR)/coll_vi_res.c

$(TEMP_PATH)coll_vi_VN_res.o : $(SRCDIR)/coll/vi_VN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_vi_VN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_vi_VN_res.c
	@$(RMV) $(TEMP_DIR)/coll_vi_VN_res.c

$(TEMP_PATH)coll_zh_res.o : $(SRCDIR)/coll/zh.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_zh_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_zh_res.c
	@$(RMV) $(TEMP_DIR)/coll_zh_res.c

$(TEMP_PATH)coll_zh__res.o : $(SRCDIR)/coll/zh_.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_zh__res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_zh__res.c
	@$(RMV) $(TEMP_DIR)/coll_zh__res.c

$(TEMP_PATH)coll_zh_CN_res.o : $(SRCDIR)/coll/zh_CN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_zh_CN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_zh_CN_res.c
	@$(RMV) $(TEMP_DIR)/coll_zh_CN_res.c

$(TEMP_PATH)coll_zh_HK_res.o : $(SRCDIR)/coll/zh_HK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_zh_HK_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_zh_HK_res.c
	@$(RMV) $(TEMP_DIR)/coll_zh_HK_res.c

$(TEMP_PATH)coll_zh_Hant_res.o : $(SRCDIR)/coll/zh_Hant.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_zh_Hant_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_zh_Hant_res.c
	@$(RMV) $(TEMP_DIR)/coll_zh_Hant_res.c

$(TEMP_PATH)coll_zh_MO_res.o : $(SRCDIR)/coll/zh_MO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_zh_MO_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_zh_MO_res.c
	@$(RMV) $(TEMP_DIR)/coll_zh_MO_res.c

$(TEMP_PATH)coll_zh_SG_res.o : $(SRCDIR)/coll/zh_SG.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_zh_SG_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_zh_SG_res.c
	@$(RMV) $(TEMP_DIR)/coll_zh_SG_res.c

$(TEMP_PATH)coll_zh_TW_res.o : $(SRCDIR)/coll/zh_TW.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_zh_TW_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_zh_TW_res.c
	@$(RMV) $(TEMP_DIR)/coll_zh_TW_res.c

$(TEMP_PATH)coll_zh_TW_STROKE_res.o : $(SRCDIR)/coll/zh_TW_STROKE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_zh_TW_STROKE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_zh_TW_STROKE_res.c
	@$(RMV) $(TEMP_DIR)/coll_zh_TW_STROKE_res.c

$(TEMP_PATH)coll_zh__PINYIN_res.o : $(SRCDIR)/coll/zh__PINYIN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_coll -d $(TEMP_DIR) $< -f coll_zh__PINYIN_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/coll_zh__PINYIN_res.c
	@$(RMV) $(TEMP_DIR)/coll_zh__PINYIN_res.c

$(TEMP_PATH)cs_res.o : $(SRCDIR)/cs.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/cs_res.c
	@$(RMV) $(TEMP_DIR)/cs_res.c

$(TEMP_PATH)cs_CZ_res.o : $(SRCDIR)/cs_CZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/cs_CZ_res.c
	@$(RMV) $(TEMP_DIR)/cs_CZ_res.c

$(TEMP_PATH)cy_res.o : $(SRCDIR)/cy.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/cy_res.c
	@$(RMV) $(TEMP_DIR)/cy_res.c

$(TEMP_PATH)cy_GB_res.o : $(SRCDIR)/cy_GB.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/cy_GB_res.c
	@$(RMV) $(TEMP_DIR)/cy_GB_res.c

$(TEMP_PATH)da_res.o : $(SRCDIR)/da.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/da_res.c
	@$(RMV) $(TEMP_DIR)/da_res.c

$(TEMP_PATH)da_DK_res.o : $(SRCDIR)/da_DK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/da_DK_res.c
	@$(RMV) $(TEMP_DIR)/da_DK_res.c

$(TEMP_PATH)de_res.o : $(SRCDIR)/de.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/de_res.c
	@$(RMV) $(TEMP_DIR)/de_res.c

$(TEMP_PATH)de_AT_res.o : $(SRCDIR)/de_AT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/de_AT_res.c
	@$(RMV) $(TEMP_DIR)/de_AT_res.c

$(TEMP_PATH)de_BE_res.o : $(SRCDIR)/de_BE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/de_BE_res.c
	@$(RMV) $(TEMP_DIR)/de_BE_res.c

$(TEMP_PATH)de_CH_res.o : $(SRCDIR)/de_CH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/de_CH_res.c
	@$(RMV) $(TEMP_DIR)/de_CH_res.c

$(TEMP_PATH)de_DE_res.o : $(SRCDIR)/de_DE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/de_DE_res.c
	@$(RMV) $(TEMP_DIR)/de_DE_res.c

$(TEMP_PATH)de_LU_res.o : $(SRCDIR)/de_LU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/de_LU_res.c
	@$(RMV) $(TEMP_DIR)/de_LU_res.c

$(TEMP_PATH)ebcdic_xml_us_cnv.o : $(SRCDIR)/ebcdic-xml-us.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ebcdic_xml_us_cnv.c
	@$(RMV) $(TEMP_DIR)/ebcdic_xml_us_cnv.c

$(TEMP_PATH)el_res.o : $(SRCDIR)/el.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/el_res.c
	@$(RMV) $(TEMP_DIR)/el_res.c

$(TEMP_PATH)el_GR_res.o : $(SRCDIR)/el_GR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/el_GR_res.c
	@$(RMV) $(TEMP_DIR)/el_GR_res.c

$(TEMP_PATH)en_res.o : $(SRCDIR)/en.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_res.c
	@$(RMV) $(TEMP_DIR)/en_res.c

$(TEMP_PATH)en_AU_res.o : $(SRCDIR)/en_AU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_AU_res.c
	@$(RMV) $(TEMP_DIR)/en_AU_res.c

$(TEMP_PATH)en_BE_res.o : $(SRCDIR)/en_BE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_BE_res.c
	@$(RMV) $(TEMP_DIR)/en_BE_res.c

$(TEMP_PATH)en_BW_res.o : $(SRCDIR)/en_BW.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_BW_res.c
	@$(RMV) $(TEMP_DIR)/en_BW_res.c

$(TEMP_PATH)en_CA_res.o : $(SRCDIR)/en_CA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_CA_res.c
	@$(RMV) $(TEMP_DIR)/en_CA_res.c

$(TEMP_PATH)en_GB_res.o : $(SRCDIR)/en_GB.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_GB_res.c
	@$(RMV) $(TEMP_DIR)/en_GB_res.c

$(TEMP_PATH)en_HK_res.o : $(SRCDIR)/en_HK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_HK_res.c
	@$(RMV) $(TEMP_DIR)/en_HK_res.c

$(TEMP_PATH)en_IE_res.o : $(SRCDIR)/en_IE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_IE_res.c
	@$(RMV) $(TEMP_DIR)/en_IE_res.c

$(TEMP_PATH)en_IN_res.o : $(SRCDIR)/en_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_IN_res.c
	@$(RMV) $(TEMP_DIR)/en_IN_res.c

$(TEMP_PATH)en_MT_res.o : $(SRCDIR)/en_MT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_MT_res.c
	@$(RMV) $(TEMP_DIR)/en_MT_res.c

$(TEMP_PATH)en_NZ_res.o : $(SRCDIR)/en_NZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_NZ_res.c
	@$(RMV) $(TEMP_DIR)/en_NZ_res.c

$(TEMP_PATH)en_PH_res.o : $(SRCDIR)/en_PH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_PH_res.c
	@$(RMV) $(TEMP_DIR)/en_PH_res.c

$(TEMP_PATH)en_PK_res.o : $(SRCDIR)/en_PK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_PK_res.c
	@$(RMV) $(TEMP_DIR)/en_PK_res.c

$(TEMP_PATH)en_RH_res.o : $(SRCDIR)/en_RH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_RH_res.c
	@$(RMV) $(TEMP_DIR)/en_RH_res.c

$(TEMP_PATH)en_SG_res.o : $(SRCDIR)/en_SG.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_SG_res.c
	@$(RMV) $(TEMP_DIR)/en_SG_res.c

$(TEMP_PATH)en_US_res.o : $(SRCDIR)/en_US.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_US_res.c
	@$(RMV) $(TEMP_DIR)/en_US_res.c

$(TEMP_PATH)en_US_POSIX_res.o : $(SRCDIR)/en_US_POSIX.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_US_POSIX_res.c
	@$(RMV) $(TEMP_DIR)/en_US_POSIX_res.c

$(TEMP_PATH)en_VI_res.o : $(SRCDIR)/en_VI.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_VI_res.c
	@$(RMV) $(TEMP_DIR)/en_VI_res.c

$(TEMP_PATH)en_ZA_res.o : $(SRCDIR)/en_ZA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_ZA_res.c
	@$(RMV) $(TEMP_DIR)/en_ZA_res.c

$(TEMP_PATH)en_ZW_res.o : $(SRCDIR)/en_ZW.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/en_ZW_res.c
	@$(RMV) $(TEMP_DIR)/en_ZW_res.c

$(TEMP_PATH)eo_res.o : $(SRCDIR)/eo.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/eo_res.c
	@$(RMV) $(TEMP_DIR)/eo_res.c

$(TEMP_PATH)es_res.o : $(SRCDIR)/es.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_res.c
	@$(RMV) $(TEMP_DIR)/es_res.c

$(TEMP_PATH)es_AR_res.o : $(SRCDIR)/es_AR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_AR_res.c
	@$(RMV) $(TEMP_DIR)/es_AR_res.c

$(TEMP_PATH)es_BO_res.o : $(SRCDIR)/es_BO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_BO_res.c
	@$(RMV) $(TEMP_DIR)/es_BO_res.c

$(TEMP_PATH)es_CL_res.o : $(SRCDIR)/es_CL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_CL_res.c
	@$(RMV) $(TEMP_DIR)/es_CL_res.c

$(TEMP_PATH)es_CO_res.o : $(SRCDIR)/es_CO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_CO_res.c
	@$(RMV) $(TEMP_DIR)/es_CO_res.c

$(TEMP_PATH)es_CR_res.o : $(SRCDIR)/es_CR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_CR_res.c
	@$(RMV) $(TEMP_DIR)/es_CR_res.c

$(TEMP_PATH)es_DO_res.o : $(SRCDIR)/es_DO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_DO_res.c
	@$(RMV) $(TEMP_DIR)/es_DO_res.c

$(TEMP_PATH)es_EC_res.o : $(SRCDIR)/es_EC.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_EC_res.c
	@$(RMV) $(TEMP_DIR)/es_EC_res.c

$(TEMP_PATH)es_ES_res.o : $(SRCDIR)/es_ES.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_ES_res.c
	@$(RMV) $(TEMP_DIR)/es_ES_res.c

$(TEMP_PATH)es_GT_res.o : $(SRCDIR)/es_GT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_GT_res.c
	@$(RMV) $(TEMP_DIR)/es_GT_res.c

$(TEMP_PATH)es_HN_res.o : $(SRCDIR)/es_HN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_HN_res.c
	@$(RMV) $(TEMP_DIR)/es_HN_res.c

$(TEMP_PATH)es_MX_res.o : $(SRCDIR)/es_MX.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_MX_res.c
	@$(RMV) $(TEMP_DIR)/es_MX_res.c

$(TEMP_PATH)es_NI_res.o : $(SRCDIR)/es_NI.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_NI_res.c
	@$(RMV) $(TEMP_DIR)/es_NI_res.c

$(TEMP_PATH)es_PA_res.o : $(SRCDIR)/es_PA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_PA_res.c
	@$(RMV) $(TEMP_DIR)/es_PA_res.c

$(TEMP_PATH)es_PE_res.o : $(SRCDIR)/es_PE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_PE_res.c
	@$(RMV) $(TEMP_DIR)/es_PE_res.c

$(TEMP_PATH)es_PR_res.o : $(SRCDIR)/es_PR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_PR_res.c
	@$(RMV) $(TEMP_DIR)/es_PR_res.c

$(TEMP_PATH)es_PY_res.o : $(SRCDIR)/es_PY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_PY_res.c
	@$(RMV) $(TEMP_DIR)/es_PY_res.c

$(TEMP_PATH)es_SV_res.o : $(SRCDIR)/es_SV.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_SV_res.c
	@$(RMV) $(TEMP_DIR)/es_SV_res.c

$(TEMP_PATH)es_US_res.o : $(SRCDIR)/es_US.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_US_res.c
	@$(RMV) $(TEMP_DIR)/es_US_res.c

$(TEMP_PATH)es_UY_res.o : $(SRCDIR)/es_UY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_UY_res.c
	@$(RMV) $(TEMP_DIR)/es_UY_res.c

$(TEMP_PATH)es_VE_res.o : $(SRCDIR)/es_VE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/es_VE_res.c
	@$(RMV) $(TEMP_DIR)/es_VE_res.c

$(TEMP_PATH)et_res.o : $(SRCDIR)/et.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/et_res.c
	@$(RMV) $(TEMP_DIR)/et_res.c

$(TEMP_PATH)et_EE_res.o : $(SRCDIR)/et_EE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/et_EE_res.c
	@$(RMV) $(TEMP_DIR)/et_EE_res.c

$(TEMP_PATH)eu_res.o : $(SRCDIR)/eu.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/eu_res.c
	@$(RMV) $(TEMP_DIR)/eu_res.c

$(TEMP_PATH)eu_ES_res.o : $(SRCDIR)/eu_ES.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/eu_ES_res.c
	@$(RMV) $(TEMP_DIR)/eu_ES_res.c

$(TEMP_PATH)fa_res.o : $(SRCDIR)/fa.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fa_res.c
	@$(RMV) $(TEMP_DIR)/fa_res.c

$(TEMP_PATH)fa_AF_res.o : $(SRCDIR)/fa_AF.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fa_AF_res.c
	@$(RMV) $(TEMP_DIR)/fa_AF_res.c

$(TEMP_PATH)fa_IR_res.o : $(SRCDIR)/fa_IR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fa_IR_res.c
	@$(RMV) $(TEMP_DIR)/fa_IR_res.c

$(TEMP_PATH)fi_res.o : $(SRCDIR)/fi.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fi_res.c
	@$(RMV) $(TEMP_DIR)/fi_res.c

$(TEMP_PATH)fi_FI_res.o : $(SRCDIR)/fi_FI.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fi_FI_res.c
	@$(RMV) $(TEMP_DIR)/fi_FI_res.c

$(TEMP_PATH)fo_res.o : $(SRCDIR)/fo.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fo_res.c
	@$(RMV) $(TEMP_DIR)/fo_res.c

$(TEMP_PATH)fo_FO_res.o : $(SRCDIR)/fo_FO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fo_FO_res.c
	@$(RMV) $(TEMP_DIR)/fo_FO_res.c

$(TEMP_PATH)fr_res.o : $(SRCDIR)/fr.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fr_res.c
	@$(RMV) $(TEMP_DIR)/fr_res.c

$(TEMP_PATH)fr_BE_res.o : $(SRCDIR)/fr_BE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fr_BE_res.c
	@$(RMV) $(TEMP_DIR)/fr_BE_res.c

$(TEMP_PATH)fr_CA_res.o : $(SRCDIR)/fr_CA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fr_CA_res.c
	@$(RMV) $(TEMP_DIR)/fr_CA_res.c

$(TEMP_PATH)fr_CH_res.o : $(SRCDIR)/fr_CH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fr_CH_res.c
	@$(RMV) $(TEMP_DIR)/fr_CH_res.c

$(TEMP_PATH)fr_FR_res.o : $(SRCDIR)/fr_FR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fr_FR_res.c
	@$(RMV) $(TEMP_DIR)/fr_FR_res.c

$(TEMP_PATH)fr_LU_res.o : $(SRCDIR)/fr_LU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/fr_LU_res.c
	@$(RMV) $(TEMP_DIR)/fr_LU_res.c

$(TEMP_PATH)ga_res.o : $(SRCDIR)/ga.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ga_res.c
	@$(RMV) $(TEMP_DIR)/ga_res.c

$(TEMP_PATH)ga_IE_res.o : $(SRCDIR)/ga_IE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ga_IE_res.c
	@$(RMV) $(TEMP_DIR)/ga_IE_res.c

$(TEMP_PATH)gb18030_cnv.o : $(SRCDIR)/gb18030.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/gb18030_cnv.c
	@$(RMV) $(TEMP_DIR)/gb18030_cnv.c

$(TEMP_PATH)gl_res.o : $(SRCDIR)/gl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/gl_res.c
	@$(RMV) $(TEMP_DIR)/gl_res.c

$(TEMP_PATH)gl_ES_res.o : $(SRCDIR)/gl_ES.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/gl_ES_res.c
	@$(RMV) $(TEMP_DIR)/gl_ES_res.c

$(TEMP_PATH)gu_res.o : $(SRCDIR)/gu.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/gu_res.c
	@$(RMV) $(TEMP_DIR)/gu_res.c

$(TEMP_PATH)gu_IN_res.o : $(SRCDIR)/gu_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/gu_IN_res.c
	@$(RMV) $(TEMP_DIR)/gu_IN_res.c

$(TEMP_PATH)gv_res.o : $(SRCDIR)/gv.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/gv_res.c
	@$(RMV) $(TEMP_DIR)/gv_res.c

$(TEMP_PATH)gv_GB_res.o : $(SRCDIR)/gv_GB.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/gv_GB_res.c
	@$(RMV) $(TEMP_DIR)/gv_GB_res.c

$(TEMP_PATH)haw_res.o : $(SRCDIR)/haw.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/haw_res.c
	@$(RMV) $(TEMP_DIR)/haw_res.c

$(TEMP_PATH)haw_US_res.o : $(SRCDIR)/haw_US.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/haw_US_res.c
	@$(RMV) $(TEMP_DIR)/haw_US_res.c

$(TEMP_PATH)he_res.o : $(SRCDIR)/he.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/he_res.c
	@$(RMV) $(TEMP_DIR)/he_res.c

$(TEMP_PATH)he_IL_res.o : $(SRCDIR)/he_IL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/he_IL_res.c
	@$(RMV) $(TEMP_DIR)/he_IL_res.c

$(TEMP_PATH)hi_res.o : $(SRCDIR)/hi.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/hi_res.c
	@$(RMV) $(TEMP_DIR)/hi_res.c

$(TEMP_PATH)hi_IN_res.o : $(SRCDIR)/hi_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/hi_IN_res.c
	@$(RMV) $(TEMP_DIR)/hi_IN_res.c

$(TEMP_PATH)hr_res.o : $(SRCDIR)/hr.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/hr_res.c
	@$(RMV) $(TEMP_DIR)/hr_res.c

$(TEMP_PATH)hr_HR_res.o : $(SRCDIR)/hr_HR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/hr_HR_res.c
	@$(RMV) $(TEMP_DIR)/hr_HR_res.c

$(TEMP_PATH)hu_res.o : $(SRCDIR)/hu.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/hu_res.c
	@$(RMV) $(TEMP_DIR)/hu_res.c

$(TEMP_PATH)hu_HU_res.o : $(SRCDIR)/hu_HU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/hu_HU_res.c
	@$(RMV) $(TEMP_DIR)/hu_HU_res.c

$(TEMP_PATH)hy_res.o : $(SRCDIR)/hy.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/hy_res.c
	@$(RMV) $(TEMP_DIR)/hy_res.c

$(TEMP_PATH)hy_AM_res.o : $(SRCDIR)/hy_AM.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/hy_AM_res.c
	@$(RMV) $(TEMP_DIR)/hy_AM_res.c

$(TEMP_PATH)hy_AM_REVISED_res.o : $(SRCDIR)/hy_AM_REVISED.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/hy_AM_REVISED_res.c
	@$(RMV) $(TEMP_DIR)/hy_AM_REVISED_res.c

$(TEMP_PATH)ibm_1006_P100_1995_cnv.o : $(SRCDIR)/ibm-1006_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1006_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1006_P100_1995_cnv.c

$(TEMP_PATH)ibm_1025_P100_1995_cnv.o : $(SRCDIR)/ibm-1025_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1025_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1025_P100_1995_cnv.c

$(TEMP_PATH)ibm_1026_P100_1995_cnv.o : $(SRCDIR)/ibm-1026_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1026_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1026_P100_1995_cnv.c

$(TEMP_PATH)ibm_1047_P100_1995_cnv.o : $(SRCDIR)/ibm-1047_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1047_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1047_P100_1995_cnv.c

$(TEMP_PATH)ibm_1051_P100_1995_cnv.o : $(SRCDIR)/ibm-1051_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1051_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1051_P100_1995_cnv.c

$(TEMP_PATH)ibm_1089_P100_1995_cnv.o : $(SRCDIR)/ibm-1089_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1089_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1089_P100_1995_cnv.c

$(TEMP_PATH)ibm_1097_P100_1995_cnv.o : $(SRCDIR)/ibm-1097_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1097_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1097_P100_1995_cnv.c

$(TEMP_PATH)ibm_1098_P100_1995_cnv.o : $(SRCDIR)/ibm-1098_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1098_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1098_P100_1995_cnv.c

$(TEMP_PATH)ibm_1112_P100_1995_cnv.o : $(SRCDIR)/ibm-1112_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1112_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1112_P100_1995_cnv.c

$(TEMP_PATH)ibm_1122_P100_1999_cnv.o : $(SRCDIR)/ibm-1122_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1122_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1122_P100_1999_cnv.c

$(TEMP_PATH)ibm_1123_P100_1995_cnv.o : $(SRCDIR)/ibm-1123_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1123_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1123_P100_1995_cnv.c

$(TEMP_PATH)ibm_1124_P100_1996_cnv.o : $(SRCDIR)/ibm-1124_P100-1996.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1124_P100_1996_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1124_P100_1996_cnv.c

$(TEMP_PATH)ibm_1125_P100_1997_cnv.o : $(SRCDIR)/ibm-1125_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1125_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1125_P100_1997_cnv.c

$(TEMP_PATH)ibm_1129_P100_1997_cnv.o : $(SRCDIR)/ibm-1129_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1129_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1129_P100_1997_cnv.c

$(TEMP_PATH)ibm_1130_P100_1997_cnv.o : $(SRCDIR)/ibm-1130_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1130_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1130_P100_1997_cnv.c

$(TEMP_PATH)ibm_1131_P100_1997_cnv.o : $(SRCDIR)/ibm-1131_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1131_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1131_P100_1997_cnv.c

$(TEMP_PATH)ibm_1132_P100_1998_cnv.o : $(SRCDIR)/ibm-1132_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1132_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1132_P100_1998_cnv.c

$(TEMP_PATH)ibm_1133_P100_1997_cnv.o : $(SRCDIR)/ibm-1133_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1133_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1133_P100_1997_cnv.c

$(TEMP_PATH)ibm_1137_P100_1999_cnv.o : $(SRCDIR)/ibm-1137_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1137_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1137_P100_1999_cnv.c

$(TEMP_PATH)ibm_1140_P100_1997_cnv.o : $(SRCDIR)/ibm-1140_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1140_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1140_P100_1997_cnv.c

$(TEMP_PATH)ibm_1141_P100_1997_cnv.o : $(SRCDIR)/ibm-1141_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1141_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1141_P100_1997_cnv.c

$(TEMP_PATH)ibm_1142_P100_1997_cnv.o : $(SRCDIR)/ibm-1142_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1142_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1142_P100_1997_cnv.c

$(TEMP_PATH)ibm_1143_P100_1997_cnv.o : $(SRCDIR)/ibm-1143_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1143_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1143_P100_1997_cnv.c

$(TEMP_PATH)ibm_1144_P100_1997_cnv.o : $(SRCDIR)/ibm-1144_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1144_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1144_P100_1997_cnv.c

$(TEMP_PATH)ibm_1145_P100_1997_cnv.o : $(SRCDIR)/ibm-1145_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1145_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1145_P100_1997_cnv.c

$(TEMP_PATH)ibm_1146_P100_1997_cnv.o : $(SRCDIR)/ibm-1146_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1146_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1146_P100_1997_cnv.c

$(TEMP_PATH)ibm_1147_P100_1997_cnv.o : $(SRCDIR)/ibm-1147_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1147_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1147_P100_1997_cnv.c

$(TEMP_PATH)ibm_1148_P100_1997_cnv.o : $(SRCDIR)/ibm-1148_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1148_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1148_P100_1997_cnv.c

$(TEMP_PATH)ibm_1149_P100_1997_cnv.o : $(SRCDIR)/ibm-1149_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1149_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1149_P100_1997_cnv.c

$(TEMP_PATH)ibm_1153_P100_1999_cnv.o : $(SRCDIR)/ibm-1153_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1153_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1153_P100_1999_cnv.c

$(TEMP_PATH)ibm_1154_P100_1999_cnv.o : $(SRCDIR)/ibm-1154_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1154_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1154_P100_1999_cnv.c

$(TEMP_PATH)ibm_1155_P100_1999_cnv.o : $(SRCDIR)/ibm-1155_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1155_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1155_P100_1999_cnv.c

$(TEMP_PATH)ibm_1156_P100_1999_cnv.o : $(SRCDIR)/ibm-1156_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1156_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1156_P100_1999_cnv.c

$(TEMP_PATH)ibm_1157_P100_1999_cnv.o : $(SRCDIR)/ibm-1157_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1157_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1157_P100_1999_cnv.c

$(TEMP_PATH)ibm_1158_P100_1999_cnv.o : $(SRCDIR)/ibm-1158_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1158_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1158_P100_1999_cnv.c

$(TEMP_PATH)ibm_1160_P100_1999_cnv.o : $(SRCDIR)/ibm-1160_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1160_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1160_P100_1999_cnv.c

$(TEMP_PATH)ibm_1162_P100_1999_cnv.o : $(SRCDIR)/ibm-1162_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1162_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1162_P100_1999_cnv.c

$(TEMP_PATH)ibm_1164_P100_1999_cnv.o : $(SRCDIR)/ibm-1164_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1164_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1164_P100_1999_cnv.c

$(TEMP_PATH)ibm_1168_P100_2002_cnv.o : $(SRCDIR)/ibm-1168_P100-2002.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1168_P100_2002_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1168_P100_2002_cnv.c

$(TEMP_PATH)ibm_1250_P100_1995_cnv.o : $(SRCDIR)/ibm-1250_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1250_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1250_P100_1995_cnv.c

$(TEMP_PATH)ibm_1251_P100_1995_cnv.o : $(SRCDIR)/ibm-1251_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1251_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1251_P100_1995_cnv.c

$(TEMP_PATH)ibm_1252_P100_2000_cnv.o : $(SRCDIR)/ibm-1252_P100-2000.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1252_P100_2000_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1252_P100_2000_cnv.c

$(TEMP_PATH)ibm_1253_P100_1995_cnv.o : $(SRCDIR)/ibm-1253_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1253_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1253_P100_1995_cnv.c

$(TEMP_PATH)ibm_1254_P100_1995_cnv.o : $(SRCDIR)/ibm-1254_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1254_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1254_P100_1995_cnv.c

$(TEMP_PATH)ibm_1255_P100_1995_cnv.o : $(SRCDIR)/ibm-1255_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1255_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1255_P100_1995_cnv.c

$(TEMP_PATH)ibm_1256_P110_1997_cnv.o : $(SRCDIR)/ibm-1256_P110-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1256_P110_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1256_P110_1997_cnv.c

$(TEMP_PATH)ibm_1257_P100_1995_cnv.o : $(SRCDIR)/ibm-1257_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1257_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1257_P100_1995_cnv.c

$(TEMP_PATH)ibm_1258_P100_1997_cnv.o : $(SRCDIR)/ibm-1258_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1258_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1258_P100_1997_cnv.c

$(TEMP_PATH)ibm_12712_P100_1998_cnv.o : $(SRCDIR)/ibm-12712_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_12712_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_12712_P100_1998_cnv.c

$(TEMP_PATH)ibm_1276_P100_1995_cnv.o : $(SRCDIR)/ibm-1276_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1276_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1276_P100_1995_cnv.c

$(TEMP_PATH)ibm_1363_P110_1997_cnv.o : $(SRCDIR)/ibm-1363_P110-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1363_P110_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1363_P110_1997_cnv.c

$(TEMP_PATH)ibm_1363_P11B_1998_cnv.o : $(SRCDIR)/ibm-1363_P11B-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1363_P11B_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1363_P11B_1998_cnv.c

$(TEMP_PATH)ibm_1364_P110_1997_cnv.o : $(SRCDIR)/ibm-1364_P110-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1364_P110_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1364_P110_1997_cnv.c

$(TEMP_PATH)ibm_1371_P100_1999_cnv.o : $(SRCDIR)/ibm-1371_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1371_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1371_P100_1999_cnv.c

$(TEMP_PATH)ibm_1373_P100_2002_cnv.o : $(SRCDIR)/ibm-1373_P100-2002.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1373_P100_2002_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1373_P100_2002_cnv.c

$(TEMP_PATH)ibm_1375_P100_2003_cnv.o : $(SRCDIR)/ibm-1375_P100-2003.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1375_P100_2003_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1375_P100_2003_cnv.c

$(TEMP_PATH)ibm_1383_P110_1999_cnv.o : $(SRCDIR)/ibm-1383_P110-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1383_P110_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1383_P110_1999_cnv.c

$(TEMP_PATH)ibm_1386_P100_2002_cnv.o : $(SRCDIR)/ibm-1386_P100-2002.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1386_P100_2002_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1386_P100_2002_cnv.c

$(TEMP_PATH)ibm_1388_P103_2001_cnv.o : $(SRCDIR)/ibm-1388_P103-2001.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1388_P103_2001_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1388_P103_2001_cnv.c

$(TEMP_PATH)ibm_1390_P110_2003_cnv.o : $(SRCDIR)/ibm-1390_P110-2003.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1390_P110_2003_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1390_P110_2003_cnv.c

$(TEMP_PATH)ibm_1399_P110_2003_cnv.o : $(SRCDIR)/ibm-1399_P110-2003.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_1399_P110_2003_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_1399_P110_2003_cnv.c

$(TEMP_PATH)ibm_16684_P110_2003_cnv.o : $(SRCDIR)/ibm-16684_P110-2003.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_16684_P110_2003_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_16684_P110_2003_cnv.c

$(TEMP_PATH)ibm_16804_X110_1999_cnv.o : $(SRCDIR)/ibm-16804_X110-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_16804_X110_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_16804_X110_1999_cnv.c

$(TEMP_PATH)ibm_273_P100_1995_cnv.o : $(SRCDIR)/ibm-273_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_273_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_273_P100_1995_cnv.c

$(TEMP_PATH)ibm_277_P100_1995_cnv.o : $(SRCDIR)/ibm-277_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_277_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_277_P100_1995_cnv.c

$(TEMP_PATH)ibm_278_P100_1995_cnv.o : $(SRCDIR)/ibm-278_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_278_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_278_P100_1995_cnv.c

$(TEMP_PATH)ibm_280_P100_1995_cnv.o : $(SRCDIR)/ibm-280_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_280_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_280_P100_1995_cnv.c

$(TEMP_PATH)ibm_284_P100_1995_cnv.o : $(SRCDIR)/ibm-284_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_284_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_284_P100_1995_cnv.c

$(TEMP_PATH)ibm_285_P100_1995_cnv.o : $(SRCDIR)/ibm-285_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_285_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_285_P100_1995_cnv.c

$(TEMP_PATH)ibm_290_P100_1995_cnv.o : $(SRCDIR)/ibm-290_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_290_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_290_P100_1995_cnv.c

$(TEMP_PATH)ibm_297_P100_1995_cnv.o : $(SRCDIR)/ibm-297_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_297_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_297_P100_1995_cnv.c

$(TEMP_PATH)ibm_33722_P120_1999_cnv.o : $(SRCDIR)/ibm-33722_P120-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_33722_P120_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_33722_P120_1999_cnv.c

$(TEMP_PATH)ibm_33722_P12A_1999_cnv.o : $(SRCDIR)/ibm-33722_P12A-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_33722_P12A_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_33722_P12A_1999_cnv.c

$(TEMP_PATH)ibm_367_P100_1995_cnv.o : $(SRCDIR)/ibm-367_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_367_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_367_P100_1995_cnv.c

$(TEMP_PATH)ibm_37_P100_1995_cnv.o : $(SRCDIR)/ibm-37_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_37_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_37_P100_1995_cnv.c

$(TEMP_PATH)ibm_420_X120_1999_cnv.o : $(SRCDIR)/ibm-420_X120-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_420_X120_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_420_X120_1999_cnv.c

$(TEMP_PATH)ibm_424_P100_1995_cnv.o : $(SRCDIR)/ibm-424_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_424_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_424_P100_1995_cnv.c

$(TEMP_PATH)ibm_437_P100_1995_cnv.o : $(SRCDIR)/ibm-437_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_437_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_437_P100_1995_cnv.c

$(TEMP_PATH)ibm_4517_P100_2005_cnv.o : $(SRCDIR)/ibm-4517_P100-2005.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_4517_P100_2005_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_4517_P100_2005_cnv.c

$(TEMP_PATH)ibm_4899_P100_1998_cnv.o : $(SRCDIR)/ibm-4899_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_4899_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_4899_P100_1998_cnv.c

$(TEMP_PATH)ibm_4909_P100_1999_cnv.o : $(SRCDIR)/ibm-4909_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_4909_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_4909_P100_1999_cnv.c

$(TEMP_PATH)ibm_4971_P100_1999_cnv.o : $(SRCDIR)/ibm-4971_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_4971_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_4971_P100_1999_cnv.c

$(TEMP_PATH)ibm_500_P100_1995_cnv.o : $(SRCDIR)/ibm-500_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_500_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_500_P100_1995_cnv.c

$(TEMP_PATH)ibm_5123_P100_1999_cnv.o : $(SRCDIR)/ibm-5123_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_5123_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_5123_P100_1999_cnv.c

$(TEMP_PATH)ibm_5346_P100_1998_cnv.o : $(SRCDIR)/ibm-5346_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_5346_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_5346_P100_1998_cnv.c

$(TEMP_PATH)ibm_5347_P100_1998_cnv.o : $(SRCDIR)/ibm-5347_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_5347_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_5347_P100_1998_cnv.c

$(TEMP_PATH)ibm_5348_P100_1997_cnv.o : $(SRCDIR)/ibm-5348_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_5348_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_5348_P100_1997_cnv.c

$(TEMP_PATH)ibm_5349_P100_1998_cnv.o : $(SRCDIR)/ibm-5349_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_5349_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_5349_P100_1998_cnv.c

$(TEMP_PATH)ibm_5350_P100_1998_cnv.o : $(SRCDIR)/ibm-5350_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_5350_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_5350_P100_1998_cnv.c

$(TEMP_PATH)ibm_5351_P100_1998_cnv.o : $(SRCDIR)/ibm-5351_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_5351_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_5351_P100_1998_cnv.c

$(TEMP_PATH)ibm_5352_P100_1998_cnv.o : $(SRCDIR)/ibm-5352_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_5352_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_5352_P100_1998_cnv.c

$(TEMP_PATH)ibm_5353_P100_1998_cnv.o : $(SRCDIR)/ibm-5353_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_5353_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_5353_P100_1998_cnv.c

$(TEMP_PATH)ibm_5354_P100_1998_cnv.o : $(SRCDIR)/ibm-5354_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_5354_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_5354_P100_1998_cnv.c

$(TEMP_PATH)ibm_5478_P100_1995_cnv.o : $(SRCDIR)/ibm-5478_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_5478_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_5478_P100_1995_cnv.c

$(TEMP_PATH)ibm_737_P100_1997_cnv.o : $(SRCDIR)/ibm-737_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_737_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_737_P100_1997_cnv.c

$(TEMP_PATH)ibm_775_P100_1996_cnv.o : $(SRCDIR)/ibm-775_P100-1996.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_775_P100_1996_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_775_P100_1996_cnv.c

$(TEMP_PATH)ibm_803_P100_1999_cnv.o : $(SRCDIR)/ibm-803_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_803_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_803_P100_1999_cnv.c

$(TEMP_PATH)ibm_813_P100_1995_cnv.o : $(SRCDIR)/ibm-813_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_813_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_813_P100_1995_cnv.c

$(TEMP_PATH)ibm_838_P100_1995_cnv.o : $(SRCDIR)/ibm-838_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_838_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_838_P100_1995_cnv.c

$(TEMP_PATH)ibm_8482_P100_1999_cnv.o : $(SRCDIR)/ibm-8482_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_8482_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_8482_P100_1999_cnv.c

$(TEMP_PATH)ibm_850_P100_1995_cnv.o : $(SRCDIR)/ibm-850_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_850_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_850_P100_1995_cnv.c

$(TEMP_PATH)ibm_851_P100_1995_cnv.o : $(SRCDIR)/ibm-851_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_851_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_851_P100_1995_cnv.c

$(TEMP_PATH)ibm_852_P100_1995_cnv.o : $(SRCDIR)/ibm-852_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_852_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_852_P100_1995_cnv.c

$(TEMP_PATH)ibm_855_P100_1995_cnv.o : $(SRCDIR)/ibm-855_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_855_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_855_P100_1995_cnv.c

$(TEMP_PATH)ibm_856_P100_1995_cnv.o : $(SRCDIR)/ibm-856_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_856_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_856_P100_1995_cnv.c

$(TEMP_PATH)ibm_857_P100_1995_cnv.o : $(SRCDIR)/ibm-857_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_857_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_857_P100_1995_cnv.c

$(TEMP_PATH)ibm_858_P100_1997_cnv.o : $(SRCDIR)/ibm-858_P100-1997.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_858_P100_1997_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_858_P100_1997_cnv.c

$(TEMP_PATH)ibm_860_P100_1995_cnv.o : $(SRCDIR)/ibm-860_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_860_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_860_P100_1995_cnv.c

$(TEMP_PATH)ibm_861_P100_1995_cnv.o : $(SRCDIR)/ibm-861_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_861_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_861_P100_1995_cnv.c

$(TEMP_PATH)ibm_862_P100_1995_cnv.o : $(SRCDIR)/ibm-862_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_862_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_862_P100_1995_cnv.c

$(TEMP_PATH)ibm_863_P100_1995_cnv.o : $(SRCDIR)/ibm-863_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_863_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_863_P100_1995_cnv.c

$(TEMP_PATH)ibm_864_X110_1999_cnv.o : $(SRCDIR)/ibm-864_X110-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_864_X110_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_864_X110_1999_cnv.c

$(TEMP_PATH)ibm_865_P100_1995_cnv.o : $(SRCDIR)/ibm-865_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_865_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_865_P100_1995_cnv.c

$(TEMP_PATH)ibm_866_P100_1995_cnv.o : $(SRCDIR)/ibm-866_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_866_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_866_P100_1995_cnv.c

$(TEMP_PATH)ibm_867_P100_1998_cnv.o : $(SRCDIR)/ibm-867_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_867_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_867_P100_1998_cnv.c

$(TEMP_PATH)ibm_868_P100_1995_cnv.o : $(SRCDIR)/ibm-868_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_868_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_868_P100_1995_cnv.c

$(TEMP_PATH)ibm_869_P100_1995_cnv.o : $(SRCDIR)/ibm-869_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_869_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_869_P100_1995_cnv.c

$(TEMP_PATH)ibm_870_P100_1995_cnv.o : $(SRCDIR)/ibm-870_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_870_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_870_P100_1995_cnv.c

$(TEMP_PATH)ibm_871_P100_1995_cnv.o : $(SRCDIR)/ibm-871_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_871_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_871_P100_1995_cnv.c

$(TEMP_PATH)ibm_874_P100_1995_cnv.o : $(SRCDIR)/ibm-874_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_874_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_874_P100_1995_cnv.c

$(TEMP_PATH)ibm_875_P100_1995_cnv.o : $(SRCDIR)/ibm-875_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_875_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_875_P100_1995_cnv.c

$(TEMP_PATH)ibm_878_P100_1996_cnv.o : $(SRCDIR)/ibm-878_P100-1996.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_878_P100_1996_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_878_P100_1996_cnv.c

$(TEMP_PATH)ibm_897_P100_1995_cnv.o : $(SRCDIR)/ibm-897_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_897_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_897_P100_1995_cnv.c

$(TEMP_PATH)ibm_9005_X100_2005_cnv.o : $(SRCDIR)/ibm-9005_X100-2005.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_9005_X100_2005_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_9005_X100_2005_cnv.c

$(TEMP_PATH)ibm_901_P100_1999_cnv.o : $(SRCDIR)/ibm-901_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_901_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_901_P100_1999_cnv.c

$(TEMP_PATH)ibm_902_P100_1999_cnv.o : $(SRCDIR)/ibm-902_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_902_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_902_P100_1999_cnv.c

$(TEMP_PATH)ibm_9067_X100_2005_cnv.o : $(SRCDIR)/ibm-9067_X100-2005.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_9067_X100_2005_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_9067_X100_2005_cnv.c

$(TEMP_PATH)ibm_912_P100_1995_cnv.o : $(SRCDIR)/ibm-912_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_912_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_912_P100_1995_cnv.c

$(TEMP_PATH)ibm_913_P100_2000_cnv.o : $(SRCDIR)/ibm-913_P100-2000.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_913_P100_2000_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_913_P100_2000_cnv.c

$(TEMP_PATH)ibm_914_P100_1995_cnv.o : $(SRCDIR)/ibm-914_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_914_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_914_P100_1995_cnv.c

$(TEMP_PATH)ibm_915_P100_1995_cnv.o : $(SRCDIR)/ibm-915_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_915_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_915_P100_1995_cnv.c

$(TEMP_PATH)ibm_916_P100_1995_cnv.o : $(SRCDIR)/ibm-916_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_916_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_916_P100_1995_cnv.c

$(TEMP_PATH)ibm_918_P100_1995_cnv.o : $(SRCDIR)/ibm-918_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_918_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_918_P100_1995_cnv.c

$(TEMP_PATH)ibm_920_P100_1995_cnv.o : $(SRCDIR)/ibm-920_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_920_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_920_P100_1995_cnv.c

$(TEMP_PATH)ibm_921_P100_1995_cnv.o : $(SRCDIR)/ibm-921_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_921_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_921_P100_1995_cnv.c

$(TEMP_PATH)ibm_922_P100_1999_cnv.o : $(SRCDIR)/ibm-922_P100-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_922_P100_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_922_P100_1999_cnv.c

$(TEMP_PATH)ibm_923_P100_1998_cnv.o : $(SRCDIR)/ibm-923_P100-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_923_P100_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_923_P100_1998_cnv.c

$(TEMP_PATH)ibm_930_P120_1999_cnv.o : $(SRCDIR)/ibm-930_P120-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_930_P120_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_930_P120_1999_cnv.c

$(TEMP_PATH)ibm_933_P110_1995_cnv.o : $(SRCDIR)/ibm-933_P110-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_933_P110_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_933_P110_1995_cnv.c

$(TEMP_PATH)ibm_935_P110_1999_cnv.o : $(SRCDIR)/ibm-935_P110-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_935_P110_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_935_P110_1999_cnv.c

$(TEMP_PATH)ibm_937_P110_1999_cnv.o : $(SRCDIR)/ibm-937_P110-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_937_P110_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_937_P110_1999_cnv.c

$(TEMP_PATH)ibm_939_P120_1999_cnv.o : $(SRCDIR)/ibm-939_P120-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_939_P120_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_939_P120_1999_cnv.c

$(TEMP_PATH)ibm_942_P12A_1999_cnv.o : $(SRCDIR)/ibm-942_P12A-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_942_P12A_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_942_P12A_1999_cnv.c

$(TEMP_PATH)ibm_943_P130_1999_cnv.o : $(SRCDIR)/ibm-943_P130-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_943_P130_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_943_P130_1999_cnv.c

$(TEMP_PATH)ibm_943_P15A_2003_cnv.o : $(SRCDIR)/ibm-943_P15A-2003.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_943_P15A_2003_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_943_P15A_2003_cnv.c

$(TEMP_PATH)ibm_9447_P100_2002_cnv.o : $(SRCDIR)/ibm-9447_P100-2002.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_9447_P100_2002_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_9447_P100_2002_cnv.c

$(TEMP_PATH)ibm_9448_X100_2005_cnv.o : $(SRCDIR)/ibm-9448_X100-2005.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_9448_X100_2005_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_9448_X100_2005_cnv.c

$(TEMP_PATH)ibm_9449_P100_2002_cnv.o : $(SRCDIR)/ibm-9449_P100-2002.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_9449_P100_2002_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_9449_P100_2002_cnv.c

$(TEMP_PATH)ibm_949_P110_1999_cnv.o : $(SRCDIR)/ibm-949_P110-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_949_P110_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_949_P110_1999_cnv.c

$(TEMP_PATH)ibm_949_P11A_1999_cnv.o : $(SRCDIR)/ibm-949_P11A-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_949_P11A_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_949_P11A_1999_cnv.c

$(TEMP_PATH)ibm_950_P110_1999_cnv.o : $(SRCDIR)/ibm-950_P110-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_950_P110_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_950_P110_1999_cnv.c

$(TEMP_PATH)ibm_954_P101_2000_cnv.o : $(SRCDIR)/ibm-954_P101-2000.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_954_P101_2000_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_954_P101_2000_cnv.c

$(TEMP_PATH)ibm_964_P110_1999_cnv.o : $(SRCDIR)/ibm-964_P110-1999.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_964_P110_1999_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_964_P110_1999_cnv.c

$(TEMP_PATH)ibm_970_P110_1995_cnv.o : $(SRCDIR)/ibm-970_P110-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_970_P110_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_970_P110_1995_cnv.c

$(TEMP_PATH)ibm_971_P100_1995_cnv.o : $(SRCDIR)/ibm-971_P100-1995.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ibm_971_P100_1995_cnv.c
	@$(RMV) $(TEMP_DIR)/ibm_971_P100_1995_cnv.c

$(TEMP_PATH)icu_internal_25546_cnv.o : $(SRCDIR)/icu-internal-25546.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/icu_internal_25546_cnv.c
	@$(RMV) $(TEMP_DIR)/icu_internal_25546_cnv.c

$(TEMP_PATH)id_res.o : $(SRCDIR)/id.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/id_res.c
	@$(RMV) $(TEMP_DIR)/id_res.c

$(TEMP_PATH)id_ID_res.o : $(SRCDIR)/id_ID.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/id_ID_res.c
	@$(RMV) $(TEMP_DIR)/id_ID_res.c

$(TEMP_PATH)in_res.o : $(SRCDIR)/in.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/in_res.c
	@$(RMV) $(TEMP_DIR)/in_res.c

$(TEMP_PATH)in_ID_res.o : $(SRCDIR)/in_ID.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/in_ID_res.c
	@$(RMV) $(TEMP_DIR)/in_ID_res.c

$(TEMP_PATH)invuca_icu.o : $(SRCDIR)/invuca.icu
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/invuca_icu.c
	@$(RMV) $(TEMP_DIR)/invuca_icu.c

$(TEMP_PATH)is_res.o : $(SRCDIR)/is.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/is_res.c
	@$(RMV) $(TEMP_DIR)/is_res.c

$(TEMP_PATH)is_IS_res.o : $(SRCDIR)/is_IS.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/is_IS_res.c
	@$(RMV) $(TEMP_DIR)/is_IS_res.c

$(TEMP_PATH)iso_8859_10_1998_cnv.o : $(SRCDIR)/iso-8859_10-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/iso_8859_10_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/iso_8859_10_1998_cnv.c

$(TEMP_PATH)iso_8859_11_2001_cnv.o : $(SRCDIR)/iso-8859_11-2001.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/iso_8859_11_2001_cnv.c
	@$(RMV) $(TEMP_DIR)/iso_8859_11_2001_cnv.c

$(TEMP_PATH)iso_8859_14_1998_cnv.o : $(SRCDIR)/iso-8859_14-1998.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/iso_8859_14_1998_cnv.c
	@$(RMV) $(TEMP_DIR)/iso_8859_14_1998_cnv.c

$(TEMP_PATH)iso_ir_165_cnv.o : $(SRCDIR)/iso-ir-165.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/iso_ir_165_cnv.c
	@$(RMV) $(TEMP_DIR)/iso_ir_165_cnv.c

$(TEMP_PATH)it_res.o : $(SRCDIR)/it.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/it_res.c
	@$(RMV) $(TEMP_DIR)/it_res.c

$(TEMP_PATH)it_CH_res.o : $(SRCDIR)/it_CH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/it_CH_res.c
	@$(RMV) $(TEMP_DIR)/it_CH_res.c

$(TEMP_PATH)it_IT_res.o : $(SRCDIR)/it_IT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/it_IT_res.c
	@$(RMV) $(TEMP_DIR)/it_IT_res.c

$(TEMP_PATH)iw_res.o : $(SRCDIR)/iw.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/iw_res.c
	@$(RMV) $(TEMP_DIR)/iw_res.c

$(TEMP_PATH)iw_IL_res.o : $(SRCDIR)/iw_IL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/iw_IL_res.c
	@$(RMV) $(TEMP_DIR)/iw_IL_res.c

$(TEMP_PATH)ja_res.o : $(SRCDIR)/ja.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ja_res.c
	@$(RMV) $(TEMP_DIR)/ja_res.c

$(TEMP_PATH)ja_JP_res.o : $(SRCDIR)/ja_JP.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ja_JP_res.c
	@$(RMV) $(TEMP_DIR)/ja_JP_res.c

$(TEMP_PATH)ja_JP_TRADITIONAL_res.o : $(SRCDIR)/ja_JP_TRADITIONAL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ja_JP_TRADITIONAL_res.c
	@$(RMV) $(TEMP_DIR)/ja_JP_TRADITIONAL_res.c

$(TEMP_PATH)jisx_208_cnv.o : $(SRCDIR)/jisx-208.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/jisx_208_cnv.c
	@$(RMV) $(TEMP_DIR)/jisx_208_cnv.c

$(TEMP_PATH)jisx_212_cnv.o : $(SRCDIR)/jisx-212.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/jisx_212_cnv.c
	@$(RMV) $(TEMP_DIR)/jisx_212_cnv.c

$(TEMP_PATH)kk_res.o : $(SRCDIR)/kk.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/kk_res.c
	@$(RMV) $(TEMP_DIR)/kk_res.c

$(TEMP_PATH)kk_KZ_res.o : $(SRCDIR)/kk_KZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/kk_KZ_res.c
	@$(RMV) $(TEMP_DIR)/kk_KZ_res.c

$(TEMP_PATH)kl_res.o : $(SRCDIR)/kl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/kl_res.c
	@$(RMV) $(TEMP_DIR)/kl_res.c

$(TEMP_PATH)kl_GL_res.o : $(SRCDIR)/kl_GL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/kl_GL_res.c
	@$(RMV) $(TEMP_DIR)/kl_GL_res.c

$(TEMP_PATH)kn_res.o : $(SRCDIR)/kn.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/kn_res.c
	@$(RMV) $(TEMP_DIR)/kn_res.c

$(TEMP_PATH)kn_IN_res.o : $(SRCDIR)/kn_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/kn_IN_res.c
	@$(RMV) $(TEMP_DIR)/kn_IN_res.c

$(TEMP_PATH)ko_res.o : $(SRCDIR)/ko.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ko_res.c
	@$(RMV) $(TEMP_DIR)/ko_res.c

$(TEMP_PATH)ko_KR_res.o : $(SRCDIR)/ko_KR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ko_KR_res.c
	@$(RMV) $(TEMP_DIR)/ko_KR_res.c

$(TEMP_PATH)kok_res.o : $(SRCDIR)/kok.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/kok_res.c
	@$(RMV) $(TEMP_DIR)/kok_res.c

$(TEMP_PATH)kok_IN_res.o : $(SRCDIR)/kok_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/kok_IN_res.c
	@$(RMV) $(TEMP_DIR)/kok_IN_res.c

$(TEMP_PATH)kw_res.o : $(SRCDIR)/kw.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/kw_res.c
	@$(RMV) $(TEMP_DIR)/kw_res.c

$(TEMP_PATH)kw_GB_res.o : $(SRCDIR)/kw_GB.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/kw_GB_res.c
	@$(RMV) $(TEMP_DIR)/kw_GB_res.c

$(TEMP_PATH)lmb_excp_cnv.o : $(SRCDIR)/lmb-excp.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/lmb_excp_cnv.c
	@$(RMV) $(TEMP_DIR)/lmb_excp_cnv.c

$(TEMP_PATH)lt_res.o : $(SRCDIR)/lt.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/lt_res.c
	@$(RMV) $(TEMP_DIR)/lt_res.c

$(TEMP_PATH)lt_LT_res.o : $(SRCDIR)/lt_LT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/lt_LT_res.c
	@$(RMV) $(TEMP_DIR)/lt_LT_res.c

$(TEMP_PATH)lv_res.o : $(SRCDIR)/lv.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/lv_res.c
	@$(RMV) $(TEMP_DIR)/lv_res.c

$(TEMP_PATH)lv_LV_res.o : $(SRCDIR)/lv_LV.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/lv_LV_res.c
	@$(RMV) $(TEMP_DIR)/lv_LV_res.c

$(TEMP_PATH)macos_0_2_10.2_cnv.o : $(SRCDIR)/macos-0_2-10.2.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/macos_0_2_10.2_cnv.c
	@$(RMV) $(TEMP_DIR)/macos_0_2_10.2_cnv.c

$(TEMP_PATH)macos_2566_10.2_cnv.o : $(SRCDIR)/macos-2566-10.2.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/macos_2566_10.2_cnv.c
	@$(RMV) $(TEMP_DIR)/macos_2566_10.2_cnv.c

$(TEMP_PATH)macos_29_10.2_cnv.o : $(SRCDIR)/macos-29-10.2.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/macos_29_10.2_cnv.c
	@$(RMV) $(TEMP_DIR)/macos_29_10.2_cnv.c

$(TEMP_PATH)macos_35_10.2_cnv.o : $(SRCDIR)/macos-35-10.2.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/macos_35_10.2_cnv.c
	@$(RMV) $(TEMP_DIR)/macos_35_10.2_cnv.c

$(TEMP_PATH)macos_6_2_10.4_cnv.o : $(SRCDIR)/macos-6_2-10.4.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/macos_6_2_10.4_cnv.c
	@$(RMV) $(TEMP_DIR)/macos_6_2_10.4_cnv.c

$(TEMP_PATH)macos_7_3_10.2_cnv.o : $(SRCDIR)/macos-7_3-10.2.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/macos_7_3_10.2_cnv.c
	@$(RMV) $(TEMP_DIR)/macos_7_3_10.2_cnv.c

$(TEMP_PATH)mk_res.o : $(SRCDIR)/mk.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/mk_res.c
	@$(RMV) $(TEMP_DIR)/mk_res.c

$(TEMP_PATH)mk_MK_res.o : $(SRCDIR)/mk_MK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/mk_MK_res.c
	@$(RMV) $(TEMP_DIR)/mk_MK_res.c

$(TEMP_PATH)ml_res.o : $(SRCDIR)/ml.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ml_res.c
	@$(RMV) $(TEMP_DIR)/ml_res.c

$(TEMP_PATH)ml_IN_res.o : $(SRCDIR)/ml_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ml_IN_res.c
	@$(RMV) $(TEMP_DIR)/ml_IN_res.c

$(TEMP_PATH)mr_res.o : $(SRCDIR)/mr.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/mr_res.c
	@$(RMV) $(TEMP_DIR)/mr_res.c

$(TEMP_PATH)mr_IN_res.o : $(SRCDIR)/mr_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/mr_IN_res.c
	@$(RMV) $(TEMP_DIR)/mr_IN_res.c

$(TEMP_PATH)ms_res.o : $(SRCDIR)/ms.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ms_res.c
	@$(RMV) $(TEMP_DIR)/ms_res.c

$(TEMP_PATH)ms_BN_res.o : $(SRCDIR)/ms_BN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ms_BN_res.c
	@$(RMV) $(TEMP_DIR)/ms_BN_res.c

$(TEMP_PATH)ms_MY_res.o : $(SRCDIR)/ms_MY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ms_MY_res.c
	@$(RMV) $(TEMP_DIR)/ms_MY_res.c

$(TEMP_PATH)mt_res.o : $(SRCDIR)/mt.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/mt_res.c
	@$(RMV) $(TEMP_DIR)/mt_res.c

$(TEMP_PATH)mt_MT_res.o : $(SRCDIR)/mt_MT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/mt_MT_res.c
	@$(RMV) $(TEMP_DIR)/mt_MT_res.c

$(TEMP_PATH)nb_res.o : $(SRCDIR)/nb.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/nb_res.c
	@$(RMV) $(TEMP_DIR)/nb_res.c

$(TEMP_PATH)nb_NO_res.o : $(SRCDIR)/nb_NO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/nb_NO_res.c
	@$(RMV) $(TEMP_DIR)/nb_NO_res.c

$(TEMP_PATH)nl_res.o : $(SRCDIR)/nl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/nl_res.c
	@$(RMV) $(TEMP_DIR)/nl_res.c

$(TEMP_PATH)nl_BE_res.o : $(SRCDIR)/nl_BE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/nl_BE_res.c
	@$(RMV) $(TEMP_DIR)/nl_BE_res.c

$(TEMP_PATH)nl_NL_res.o : $(SRCDIR)/nl_NL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/nl_NL_res.c
	@$(RMV) $(TEMP_DIR)/nl_NL_res.c

$(TEMP_PATH)nn_res.o : $(SRCDIR)/nn.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/nn_res.c
	@$(RMV) $(TEMP_DIR)/nn_res.c

$(TEMP_PATH)nn_NO_res.o : $(SRCDIR)/nn_NO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/nn_NO_res.c
	@$(RMV) $(TEMP_DIR)/nn_NO_res.c

$(TEMP_PATH)no_res.o : $(SRCDIR)/no.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/no_res.c
	@$(RMV) $(TEMP_DIR)/no_res.c

$(TEMP_PATH)no_NO_res.o : $(SRCDIR)/no_NO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/no_NO_res.c
	@$(RMV) $(TEMP_DIR)/no_NO_res.c

$(TEMP_PATH)no_NO_NY_res.o : $(SRCDIR)/no_NO_NY.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/no_NO_NY_res.c
	@$(RMV) $(TEMP_DIR)/no_NO_NY_res.c

$(TEMP_PATH)om_res.o : $(SRCDIR)/om.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/om_res.c
	@$(RMV) $(TEMP_DIR)/om_res.c

$(TEMP_PATH)om_ET_res.o : $(SRCDIR)/om_ET.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/om_ET_res.c
	@$(RMV) $(TEMP_DIR)/om_ET_res.c

$(TEMP_PATH)om_KE_res.o : $(SRCDIR)/om_KE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/om_KE_res.c
	@$(RMV) $(TEMP_DIR)/om_KE_res.c

$(TEMP_PATH)or_res.o : $(SRCDIR)/or.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/or_res.c
	@$(RMV) $(TEMP_DIR)/or_res.c

$(TEMP_PATH)or_IN_res.o : $(SRCDIR)/or_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/or_IN_res.c
	@$(RMV) $(TEMP_DIR)/or_IN_res.c

$(TEMP_PATH)pa_res.o : $(SRCDIR)/pa.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/pa_res.c
	@$(RMV) $(TEMP_DIR)/pa_res.c

$(TEMP_PATH)pa_IN_res.o : $(SRCDIR)/pa_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/pa_IN_res.c
	@$(RMV) $(TEMP_DIR)/pa_IN_res.c

$(TEMP_PATH)pl_res.o : $(SRCDIR)/pl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/pl_res.c
	@$(RMV) $(TEMP_DIR)/pl_res.c

$(TEMP_PATH)pl_PL_res.o : $(SRCDIR)/pl_PL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/pl_PL_res.c
	@$(RMV) $(TEMP_DIR)/pl_PL_res.c

$(TEMP_PATH)pnames_icu.o : $(SRCDIR)/pnames.icu
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/pnames_icu.c
	@$(RMV) $(TEMP_DIR)/pnames_icu.c

$(TEMP_PATH)ps_res.o : $(SRCDIR)/ps.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ps_res.c
	@$(RMV) $(TEMP_DIR)/ps_res.c

$(TEMP_PATH)ps_AF_res.o : $(SRCDIR)/ps_AF.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ps_AF_res.c
	@$(RMV) $(TEMP_DIR)/ps_AF_res.c

$(TEMP_PATH)pt_res.o : $(SRCDIR)/pt.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/pt_res.c
	@$(RMV) $(TEMP_DIR)/pt_res.c

$(TEMP_PATH)pt_BR_res.o : $(SRCDIR)/pt_BR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/pt_BR_res.c
	@$(RMV) $(TEMP_DIR)/pt_BR_res.c

$(TEMP_PATH)pt_PT_res.o : $(SRCDIR)/pt_PT.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/pt_PT_res.c
	@$(RMV) $(TEMP_DIR)/pt_PT_res.c

$(TEMP_PATH)rbnf_da_res.o : $(SRCDIR)/rbnf/da.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_da_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_da_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_da_res.c

$(TEMP_PATH)rbnf_de_res.o : $(SRCDIR)/rbnf/de.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_de_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_de_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_de_res.c

$(TEMP_PATH)rbnf_en_res.o : $(SRCDIR)/rbnf/en.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_en_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_en_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_en_res.c

$(TEMP_PATH)rbnf_en_GB_res.o : $(SRCDIR)/rbnf/en_GB.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_en_GB_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_en_GB_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_en_GB_res.c

$(TEMP_PATH)rbnf_eo_res.o : $(SRCDIR)/rbnf/eo.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_eo_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_eo_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_eo_res.c

$(TEMP_PATH)rbnf_es_res.o : $(SRCDIR)/rbnf/es.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_es_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_es_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_es_res.c

$(TEMP_PATH)rbnf_fa_res.o : $(SRCDIR)/rbnf/fa.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_fa_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_fa_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_fa_res.c

$(TEMP_PATH)rbnf_fa_AF_res.o : $(SRCDIR)/rbnf/fa_AF.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_fa_AF_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_fa_AF_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_fa_AF_res.c

$(TEMP_PATH)rbnf_fr_res.o : $(SRCDIR)/rbnf/fr.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_fr_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_fr_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_fr_res.c

$(TEMP_PATH)rbnf_fr_BE_res.o : $(SRCDIR)/rbnf/fr_BE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_fr_BE_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_fr_BE_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_fr_BE_res.c

$(TEMP_PATH)rbnf_fr_CH_res.o : $(SRCDIR)/rbnf/fr_CH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_fr_CH_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_fr_CH_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_fr_CH_res.c

$(TEMP_PATH)rbnf_ga_res.o : $(SRCDIR)/rbnf/ga.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_ga_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_ga_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_ga_res.c

$(TEMP_PATH)rbnf_he_res.o : $(SRCDIR)/rbnf/he.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_he_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_he_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_he_res.c

$(TEMP_PATH)rbnf_it_res.o : $(SRCDIR)/rbnf/it.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_it_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_it_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_it_res.c

$(TEMP_PATH)rbnf_ja_res.o : $(SRCDIR)/rbnf/ja.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_ja_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_ja_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_ja_res.c

$(TEMP_PATH)rbnf_mt_res.o : $(SRCDIR)/rbnf/mt.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_mt_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_mt_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_mt_res.c

$(TEMP_PATH)rbnf_nl_res.o : $(SRCDIR)/rbnf/nl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_nl_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_nl_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_nl_res.c

$(TEMP_PATH)rbnf_pl_res.o : $(SRCDIR)/rbnf/pl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_pl_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_pl_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_pl_res.c

$(TEMP_PATH)rbnf_pt_res.o : $(SRCDIR)/rbnf/pt.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_pt_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_pt_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_pt_res.c

$(TEMP_PATH)rbnf_res_index_res.o : $(SRCDIR)/rbnf/res_index.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_res_index_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_res_index_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_res_index_res.c

$(TEMP_PATH)rbnf_root_res.o : $(SRCDIR)/rbnf/root.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_root_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_root_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_root_res.c

$(TEMP_PATH)rbnf_ru_res.o : $(SRCDIR)/rbnf/ru.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_ru_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_ru_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_ru_res.c

$(TEMP_PATH)rbnf_sv_res.o : $(SRCDIR)/rbnf/sv.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_sv_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_sv_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_sv_res.c

$(TEMP_PATH)rbnf_th_res.o : $(SRCDIR)/rbnf/th.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_th_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_th_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_th_res.c

$(TEMP_PATH)rbnf_uk_res.o : $(SRCDIR)/rbnf/uk.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_rbnf -d $(TEMP_DIR) $< -f rbnf_uk_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/rbnf_uk_res.c
	@$(RMV) $(TEMP_DIR)/rbnf_uk_res.c

$(TEMP_PATH)res_index_res.o : $(SRCDIR)/res_index.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/res_index_res.c
	@$(RMV) $(TEMP_DIR)/res_index_res.c

$(TEMP_PATH)ro_res.o : $(SRCDIR)/ro.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ro_res.c
	@$(RMV) $(TEMP_DIR)/ro_res.c

$(TEMP_PATH)ro_RO_res.o : $(SRCDIR)/ro_RO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ro_RO_res.c
	@$(RMV) $(TEMP_DIR)/ro_RO_res.c

$(TEMP_PATH)root_res.o : $(SRCDIR)/root.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/root_res.c
	@$(RMV) $(TEMP_DIR)/root_res.c

$(TEMP_PATH)ru_res.o : $(SRCDIR)/ru.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ru_res.c
	@$(RMV) $(TEMP_DIR)/ru_res.c

$(TEMP_PATH)ru_RU_res.o : $(SRCDIR)/ru_RU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ru_RU_res.c
	@$(RMV) $(TEMP_DIR)/ru_RU_res.c

$(TEMP_PATH)ru_UA_res.o : $(SRCDIR)/ru_UA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ru_UA_res.c
	@$(RMV) $(TEMP_DIR)/ru_UA_res.c

$(TEMP_PATH)sh_res.o : $(SRCDIR)/sh.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sh_res.c
	@$(RMV) $(TEMP_DIR)/sh_res.c

$(TEMP_PATH)sh_CS_res.o : $(SRCDIR)/sh_CS.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sh_CS_res.c
	@$(RMV) $(TEMP_DIR)/sh_CS_res.c

$(TEMP_PATH)sh_YU_res.o : $(SRCDIR)/sh_YU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sh_YU_res.c
	@$(RMV) $(TEMP_DIR)/sh_YU_res.c

$(TEMP_PATH)sk_res.o : $(SRCDIR)/sk.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sk_res.c
	@$(RMV) $(TEMP_DIR)/sk_res.c

$(TEMP_PATH)sk_SK_res.o : $(SRCDIR)/sk_SK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sk_SK_res.c
	@$(RMV) $(TEMP_DIR)/sk_SK_res.c

$(TEMP_PATH)sl_res.o : $(SRCDIR)/sl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sl_res.c
	@$(RMV) $(TEMP_DIR)/sl_res.c

$(TEMP_PATH)sl_SI_res.o : $(SRCDIR)/sl_SI.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sl_SI_res.c
	@$(RMV) $(TEMP_DIR)/sl_SI_res.c

$(TEMP_PATH)so_res.o : $(SRCDIR)/so.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/so_res.c
	@$(RMV) $(TEMP_DIR)/so_res.c

$(TEMP_PATH)so_DJ_res.o : $(SRCDIR)/so_DJ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/so_DJ_res.c
	@$(RMV) $(TEMP_DIR)/so_DJ_res.c

$(TEMP_PATH)so_ET_res.o : $(SRCDIR)/so_ET.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/so_ET_res.c
	@$(RMV) $(TEMP_DIR)/so_ET_res.c

$(TEMP_PATH)so_KE_res.o : $(SRCDIR)/so_KE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/so_KE_res.c
	@$(RMV) $(TEMP_DIR)/so_KE_res.c

$(TEMP_PATH)so_SO_res.o : $(SRCDIR)/so_SO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/so_SO_res.c
	@$(RMV) $(TEMP_DIR)/so_SO_res.c

$(TEMP_PATH)sq_res.o : $(SRCDIR)/sq.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sq_res.c
	@$(RMV) $(TEMP_DIR)/sq_res.c

$(TEMP_PATH)sq_AL_res.o : $(SRCDIR)/sq_AL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sq_AL_res.c
	@$(RMV) $(TEMP_DIR)/sq_AL_res.c

$(TEMP_PATH)sr_res.o : $(SRCDIR)/sr.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sr_res.c
	@$(RMV) $(TEMP_DIR)/sr_res.c

$(TEMP_PATH)sr_CS_res.o : $(SRCDIR)/sr_CS.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sr_CS_res.c
	@$(RMV) $(TEMP_DIR)/sr_CS_res.c

$(TEMP_PATH)sr_Cyrl_res.o : $(SRCDIR)/sr_Cyrl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sr_Cyrl_res.c
	@$(RMV) $(TEMP_DIR)/sr_Cyrl_res.c

$(TEMP_PATH)sr_Cyrl_CS_res.o : $(SRCDIR)/sr_Cyrl_CS.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sr_Cyrl_CS_res.c
	@$(RMV) $(TEMP_DIR)/sr_Cyrl_CS_res.c

$(TEMP_PATH)sr_Cyrl_YU_res.o : $(SRCDIR)/sr_Cyrl_YU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sr_Cyrl_YU_res.c
	@$(RMV) $(TEMP_DIR)/sr_Cyrl_YU_res.c

$(TEMP_PATH)sr_Latn_res.o : $(SRCDIR)/sr_Latn.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sr_Latn_res.c
	@$(RMV) $(TEMP_DIR)/sr_Latn_res.c

$(TEMP_PATH)sr_Latn_CS_res.o : $(SRCDIR)/sr_Latn_CS.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sr_Latn_CS_res.c
	@$(RMV) $(TEMP_DIR)/sr_Latn_CS_res.c

$(TEMP_PATH)sr_Latn_YU_res.o : $(SRCDIR)/sr_Latn_YU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sr_Latn_YU_res.c
	@$(RMV) $(TEMP_DIR)/sr_Latn_YU_res.c

$(TEMP_PATH)sr_YU_res.o : $(SRCDIR)/sr_YU.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sr_YU_res.c
	@$(RMV) $(TEMP_DIR)/sr_YU_res.c

$(TEMP_PATH)sv_res.o : $(SRCDIR)/sv.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sv_res.c
	@$(RMV) $(TEMP_DIR)/sv_res.c

$(TEMP_PATH)sv_FI_res.o : $(SRCDIR)/sv_FI.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sv_FI_res.c
	@$(RMV) $(TEMP_DIR)/sv_FI_res.c

$(TEMP_PATH)sv_SE_res.o : $(SRCDIR)/sv_SE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sv_SE_res.c
	@$(RMV) $(TEMP_DIR)/sv_SE_res.c

$(TEMP_PATH)sw_res.o : $(SRCDIR)/sw.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sw_res.c
	@$(RMV) $(TEMP_DIR)/sw_res.c

$(TEMP_PATH)sw_KE_res.o : $(SRCDIR)/sw_KE.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sw_KE_res.c
	@$(RMV) $(TEMP_DIR)/sw_KE_res.c

$(TEMP_PATH)sw_TZ_res.o : $(SRCDIR)/sw_TZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/sw_TZ_res.c
	@$(RMV) $(TEMP_DIR)/sw_TZ_res.c

$(TEMP_PATH)ta_res.o : $(SRCDIR)/ta.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ta_res.c
	@$(RMV) $(TEMP_DIR)/ta_res.c

$(TEMP_PATH)ta_IN_res.o : $(SRCDIR)/ta_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ta_IN_res.c
	@$(RMV) $(TEMP_DIR)/ta_IN_res.c

$(TEMP_PATH)te_res.o : $(SRCDIR)/te.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/te_res.c
	@$(RMV) $(TEMP_DIR)/te_res.c

$(TEMP_PATH)te_IN_res.o : $(SRCDIR)/te_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/te_IN_res.c
	@$(RMV) $(TEMP_DIR)/te_IN_res.c

$(TEMP_PATH)th_res.o : $(SRCDIR)/th.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/th_res.c
	@$(RMV) $(TEMP_DIR)/th_res.c

$(TEMP_PATH)th_TH_res.o : $(SRCDIR)/th_TH.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/th_TH_res.c
	@$(RMV) $(TEMP_DIR)/th_TH_res.c

$(TEMP_PATH)th_TH_TRADITIONAL_res.o : $(SRCDIR)/th_TH_TRADITIONAL.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/th_TH_TRADITIONAL_res.c
	@$(RMV) $(TEMP_DIR)/th_TH_TRADITIONAL_res.c

$(TEMP_PATH)ti_res.o : $(SRCDIR)/ti.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ti_res.c
	@$(RMV) $(TEMP_DIR)/ti_res.c

$(TEMP_PATH)ti_ER_res.o : $(SRCDIR)/ti_ER.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ti_ER_res.c
	@$(RMV) $(TEMP_DIR)/ti_ER_res.c

$(TEMP_PATH)ti_ET_res.o : $(SRCDIR)/ti_ET.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ti_ET_res.c
	@$(RMV) $(TEMP_DIR)/ti_ET_res.c

$(TEMP_PATH)tr_res.o : $(SRCDIR)/tr.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/tr_res.c
	@$(RMV) $(TEMP_DIR)/tr_res.c

$(TEMP_PATH)tr_TR_res.o : $(SRCDIR)/tr_TR.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/tr_TR_res.c
	@$(RMV) $(TEMP_DIR)/tr_TR_res.c

$(TEMP_PATH)translit_el_res.o : $(SRCDIR)/translit/el.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_translit -d $(TEMP_DIR) $< -f translit_el_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/translit_el_res.c
	@$(RMV) $(TEMP_DIR)/translit_el_res.c

$(TEMP_PATH)translit_en_res.o : $(SRCDIR)/translit/en.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_translit -d $(TEMP_DIR) $< -f translit_en_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/translit_en_res.c
	@$(RMV) $(TEMP_DIR)/translit_en_res.c

$(TEMP_PATH)translit_root_res.o : $(SRCDIR)/translit/root.res
	$(INVOKE) $(GENCCODE) -n $(CNAME)_translit -d $(TEMP_DIR) $< -f translit_root_res
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/translit_root_res.c
	@$(RMV) $(TEMP_DIR)/translit_root_res.c

$(TEMP_PATH)ucadata_icu.o : $(SRCDIR)/ucadata.icu
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ucadata_icu.c
	@$(RMV) $(TEMP_DIR)/ucadata_icu.c

$(TEMP_PATH)uidna_spp.o : $(SRCDIR)/uidna.spp
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/uidna_spp.c
	@$(RMV) $(TEMP_DIR)/uidna_spp.c

$(TEMP_PATH)uk_res.o : $(SRCDIR)/uk.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/uk_res.c
	@$(RMV) $(TEMP_DIR)/uk_res.c

$(TEMP_PATH)uk_UA_res.o : $(SRCDIR)/uk_UA.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/uk_UA_res.c
	@$(RMV) $(TEMP_DIR)/uk_UA_res.c

$(TEMP_PATH)unames_icu.o : $(SRCDIR)/unames.icu
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/unames_icu.c
	@$(RMV) $(TEMP_DIR)/unames_icu.c

$(TEMP_PATH)ur_res.o : $(SRCDIR)/ur.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ur_res.c
	@$(RMV) $(TEMP_DIR)/ur_res.c

$(TEMP_PATH)ur_IN_res.o : $(SRCDIR)/ur_IN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ur_IN_res.c
	@$(RMV) $(TEMP_DIR)/ur_IN_res.c

$(TEMP_PATH)ur_PK_res.o : $(SRCDIR)/ur_PK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/ur_PK_res.c
	@$(RMV) $(TEMP_DIR)/ur_PK_res.c

$(TEMP_PATH)uz_res.o : $(SRCDIR)/uz.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/uz_res.c
	@$(RMV) $(TEMP_DIR)/uz_res.c

$(TEMP_PATH)uz_Cyrl_res.o : $(SRCDIR)/uz_Cyrl.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/uz_Cyrl_res.c
	@$(RMV) $(TEMP_DIR)/uz_Cyrl_res.c

$(TEMP_PATH)uz_Cyrl_UZ_res.o : $(SRCDIR)/uz_Cyrl_UZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/uz_Cyrl_UZ_res.c
	@$(RMV) $(TEMP_DIR)/uz_Cyrl_UZ_res.c

$(TEMP_PATH)uz_Latn_res.o : $(SRCDIR)/uz_Latn.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/uz_Latn_res.c
	@$(RMV) $(TEMP_DIR)/uz_Latn_res.c

$(TEMP_PATH)uz_Latn_UZ_res.o : $(SRCDIR)/uz_Latn_UZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/uz_Latn_UZ_res.c
	@$(RMV) $(TEMP_DIR)/uz_Latn_UZ_res.c

$(TEMP_PATH)uz_UZ_res.o : $(SRCDIR)/uz_UZ.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/uz_UZ_res.c
	@$(RMV) $(TEMP_DIR)/uz_UZ_res.c

$(TEMP_PATH)vi_res.o : $(SRCDIR)/vi.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/vi_res.c
	@$(RMV) $(TEMP_DIR)/vi_res.c

$(TEMP_PATH)vi_VN_res.o : $(SRCDIR)/vi_VN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/vi_VN_res.c
	@$(RMV) $(TEMP_DIR)/vi_VN_res.c

$(TEMP_PATH)windows_874_2000_cnv.o : $(SRCDIR)/windows-874-2000.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/windows_874_2000_cnv.c
	@$(RMV) $(TEMP_DIR)/windows_874_2000_cnv.c

$(TEMP_PATH)windows_936_2000_cnv.o : $(SRCDIR)/windows-936-2000.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/windows_936_2000_cnv.c
	@$(RMV) $(TEMP_DIR)/windows_936_2000_cnv.c

$(TEMP_PATH)windows_949_2000_cnv.o : $(SRCDIR)/windows-949-2000.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/windows_949_2000_cnv.c
	@$(RMV) $(TEMP_DIR)/windows_949_2000_cnv.c

$(TEMP_PATH)windows_950_2000_cnv.o : $(SRCDIR)/windows-950-2000.cnv
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/windows_950_2000_cnv.c
	@$(RMV) $(TEMP_DIR)/windows_950_2000_cnv.c

$(TEMP_PATH)zh_res.o : $(SRCDIR)/zh.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_res.c
	@$(RMV) $(TEMP_DIR)/zh_res.c

$(TEMP_PATH)zh_CN_res.o : $(SRCDIR)/zh_CN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_CN_res.c
	@$(RMV) $(TEMP_DIR)/zh_CN_res.c

$(TEMP_PATH)zh_HK_res.o : $(SRCDIR)/zh_HK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_HK_res.c
	@$(RMV) $(TEMP_DIR)/zh_HK_res.c

$(TEMP_PATH)zh_Hans_res.o : $(SRCDIR)/zh_Hans.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_Hans_res.c
	@$(RMV) $(TEMP_DIR)/zh_Hans_res.c

$(TEMP_PATH)zh_Hans_CN_res.o : $(SRCDIR)/zh_Hans_CN.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_Hans_CN_res.c
	@$(RMV) $(TEMP_DIR)/zh_Hans_CN_res.c

$(TEMP_PATH)zh_Hans_SG_res.o : $(SRCDIR)/zh_Hans_SG.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_Hans_SG_res.c
	@$(RMV) $(TEMP_DIR)/zh_Hans_SG_res.c

$(TEMP_PATH)zh_Hant_res.o : $(SRCDIR)/zh_Hant.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_Hant_res.c
	@$(RMV) $(TEMP_DIR)/zh_Hant_res.c

$(TEMP_PATH)zh_Hant_HK_res.o : $(SRCDIR)/zh_Hant_HK.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_Hant_HK_res.c
	@$(RMV) $(TEMP_DIR)/zh_Hant_HK_res.c

$(TEMP_PATH)zh_Hant_MO_res.o : $(SRCDIR)/zh_Hant_MO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_Hant_MO_res.c
	@$(RMV) $(TEMP_DIR)/zh_Hant_MO_res.c

$(TEMP_PATH)zh_Hant_TW_res.o : $(SRCDIR)/zh_Hant_TW.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_Hant_TW_res.c
	@$(RMV) $(TEMP_DIR)/zh_Hant_TW_res.c

$(TEMP_PATH)zh_MO_res.o : $(SRCDIR)/zh_MO.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_MO_res.c
	@$(RMV) $(TEMP_DIR)/zh_MO_res.c

$(TEMP_PATH)zh_SG_res.o : $(SRCDIR)/zh_SG.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_SG_res.c
	@$(RMV) $(TEMP_DIR)/zh_SG_res.c

$(TEMP_PATH)zh_TW_res.o : $(SRCDIR)/zh_TW.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zh_TW_res.c
	@$(RMV) $(TEMP_DIR)/zh_TW_res.c

$(TEMP_PATH)zoneinfo_res.o : $(SRCDIR)/zoneinfo.res
	$(INVOKE) $(GENCCODE) -n $(CNAME) -d $(TEMP_DIR) $<
	@$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/zoneinfo_res.c
	@$(RMV) $(TEMP_DIR)/zoneinfo_res.c

# List file for gencmn:
CMNLIST=./out/tmp/$(NAME)_dll.lst

$(CMNLIST): $(LISTFILES)
	cat $(LISTFILES) > $(CMNLIST)

TOCSYM= icudt36_dat 


ifneq ($(GENCCODE_ASSEMBLY),)

BASE_OBJECTS=$(NAME)_dat.o

$(TEMP_DIR)/$(NAME).dat: $(CMNLIST) $(DATAFILEPATHS)
	$(INVOKE) $(GENCMN) -c -e $(ENTRYPOINT) -n $(NAME) -s $(SRCDIR) -t dat -d $(TEMP_DIR) 0 $(CMNLIST)

$(TEMP_DIR)/$(NAME)_dat.o : $(TEMP_DIR)/$(NAME).dat
	$(INVOKE) $(GENCCODE) $(GENCCODE_ASSEMBLY) -n $(NAME) -e $(ENTRYPOINT) -d $(TEMP_DIR) $<
	$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $(TEMP_DIR)/$(NAME)_dat.s
	$(RMV) $(TEMP_DIR)/$(NAME)_dat.s

else

$(TEMP_DIR)/$(NAME)_dat.o : $(TEMP_DIR)/$(NAME)_dat.c
	$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $<

# 'TOCOBJ' contains C Table of Contents objects [if any]
$(TEMP_DIR)/$(NAME)_dat.c: $(CMNLIST)
	$(INVOKE) $(GENCMN) -e $(ENTRYPOINT) -n $(NAME) -S -s $(SRCDIR) -d $(TEMP_DIR) 0 $(CMNLIST)

TOCOBJ= $(NAME)_dat.o 

BASE_OBJECTS= $(TOCOBJ) CurrencyData_res.o af_res.o af_ZA_res.o am_res.o am_ET_res.o ar_res.o \
 ar_AE_res.o ar_BH_res.o ar_DZ_res.o ar_EG_res.o ar_IQ_res.o ar_JO_res.o \
 ar_KW_res.o ar_LB_res.o ar_LY_res.o ar_MA_res.o ar_OM_res.o ar_QA_res.o \
 ar_SA_res.o ar_SD_res.o ar_SY_res.o ar_TN_res.o ar_YE_res.o as_res.o \
 as_IN_res.o az_res.o az_AZ_res.o az_Cyrl_res.o az_Cyrl_AZ_res.o az_Latn_res.o \
 az_Latn_AZ_res.o be_res.o be_BY_res.o bg_res.o bg_BG_res.o bn_res.o \
 bn_IN_res.o brkitr_char_brk.o brkitr_en_res.o brkitr_en_US_res.o \
 brkitr_en_US_POSIX_res.o brkitr_ja_res.o brkitr_line_brk.o brkitr_res_index_res.o \
 brkitr_root_res.o brkitr_sent_brk.o brkitr_thaidict_ctd.o brkitr_title_brk.o \
 brkitr_word_brk.o brkitr_word_POSIX_brk.o brkitr_word_ja_brk.o ca_res.o \
 ca_ES_res.o cns_11643_1992_cnv.o cnvalias_icu.o coll_ar_res.o coll_ar_AE_res.o \
 coll_ar_BH_res.o coll_ar_DZ_res.o coll_ar_EG_res.o coll_ar_IQ_res.o \
 coll_ar_JO_res.o coll_ar_KW_res.o coll_ar_LB_res.o coll_ar_LY_res.o \
 coll_ar_MA_res.o coll_ar_OM_res.o coll_ar_QA_res.o coll_ar_SA_res.o \
 coll_ar_SD_res.o coll_ar_SY_res.o coll_ar_TN_res.o coll_ar_YE_res.o \
 coll_as_res.o coll_as_IN_res.o coll_be_res.o coll_be_BY_res.o coll_bg_res.o \
 coll_bg_BG_res.o coll_bn_res.o coll_ca_res.o coll_ca_ES_res.o coll_cs_res.o \
 coll_cs_CZ_res.o coll_da_res.o coll_da_DK_res.o coll_de_res.o coll_de__res.o \
 coll_de_AT_res.o coll_de_BE_res.o coll_de_CH_res.o coll_de_DE_res.o \
 coll_de_LU_res.o coll_de__PHONEBOOK_res.o coll_el_res.o coll_el_GR_res.o \
 coll_en_res.o coll_en_AU_res.o coll_en_BE_res.o coll_en_BW_res.o \
 coll_en_CA_res.o coll_en_GB_res.o coll_en_HK_res.o coll_en_IE_res.o \
 coll_en_IN_res.o coll_en_MT_res.o coll_en_NZ_res.o coll_en_PH_res.o \
 coll_en_SG_res.o coll_en_US_res.o coll_en_US_POSIX_res.o coll_en_VI_res.o \
 coll_en_ZA_res.o coll_en_ZW_res.o coll_eo_res.o coll_es_res.o coll_es__res.o \
 coll_es_AR_res.o coll_es_BO_res.o coll_es_CL_res.o coll_es_CO_res.o \
 coll_es_CR_res.o coll_es_DO_res.o coll_es_EC_res.o coll_es_ES_res.o \
 coll_es_GT_res.o coll_es_HN_res.o coll_es_MX_res.o coll_es_NI_res.o \
 coll_es_PA_res.o coll_es_PE_res.o coll_es_PR_res.o coll_es_PY_res.o \
 coll_es_SV_res.o coll_es_US_res.o coll_es_UY_res.o coll_es_VE_res.o \
 coll_es__TRADITIONAL_res.o coll_et_res.o coll_et_EE_res.o coll_fa_res.o \
 coll_fa_AF_res.o coll_fa_IR_res.o coll_fi_res.o coll_fi_FI_res.o \
 coll_fo_res.o coll_fo_FO_res.o coll_fr_res.o coll_fr_BE_res.o coll_fr_CA_res.o \
 coll_fr_CH_res.o coll_fr_FR_res.o coll_fr_LU_res.o coll_ga_res.o \
 coll_ga_IE_res.o coll_gu_res.o coll_gu_IN_res.o coll_haw_res.o coll_he_res.o \
 coll_he_IL_res.o coll_hi_res.o coll_hi__res.o coll_hi_IN_res.o coll_hi__DIRECT_res.o \
 coll_hr_res.o coll_hr_HR_res.o coll_hu_res.o coll_hu_HU_res.o coll_id_res.o \
 coll_id_ID_res.o coll_in_res.o coll_in_ID_res.o coll_is_res.o coll_is_IS_res.o \
 coll_it_res.o coll_it_CH_res.o coll_it_IT_res.o coll_iw_res.o coll_iw_IL_res.o \
 coll_ja_res.o coll_ja_JP_res.o coll_kk_res.o coll_kk_KZ_res.o coll_kl_res.o \
 coll_kl_GL_res.o coll_kn_res.o coll_kn_IN_res.o coll_ko_res.o coll_ko_KR_res.o \
 coll_kok_res.o coll_lt_res.o coll_lt_LT_res.o coll_lv_res.o coll_lv_LV_res.o \
 coll_mk_res.o coll_mk_MK_res.o coll_ml_res.o coll_mr_res.o coll_mr_IN_res.o \
 coll_ms_res.o coll_ms_BN_res.o coll_ms_MY_res.o coll_mt_res.o coll_mt_MT_res.o \
 coll_nb_res.o coll_nb_NO_res.o coll_nl_res.o coll_nl_BE_res.o coll_nl_NL_res.o \
 coll_nn_res.o coll_nn_NO_res.o coll_om_res.o coll_om_ET_res.o coll_om_KE_res.o \
 coll_or_res.o coll_pa_res.o coll_pa_IN_res.o coll_pl_res.o coll_pl_PL_res.o \
 coll_ps_res.o coll_ps_AF_res.o coll_pt_res.o coll_pt_BR_res.o coll_pt_PT_res.o \
 coll_res_index_res.o coll_ro_res.o coll_ro_RO_res.o coll_root_res.o \
 coll_ru_res.o coll_ru_RU_res.o coll_ru_UA_res.o coll_sh_res.o coll_sh_BA_res.o \
 coll_sh_YU_res.o coll_sk_res.o coll_sk_SK_res.o coll_sl_res.o coll_sl_SI_res.o \
 coll_sq_res.o coll_sq_AL_res.o coll_sr_res.o coll_sr_BA_res.o coll_sr_Cyrl_res.o \
 coll_sr_Cyrl_BA_res.o coll_sr_Cyrl_YU_res.o coll_sr_YU_res.o coll_sv_res.o \
 coll_sv_FI_res.o coll_sv_SE_res.o coll_ta_res.o coll_ta_IN_res.o \
 coll_te_res.o coll_te_IN_res.o coll_th_res.o coll_th_TH_res.o coll_tr_res.o \
 coll_tr_TR_res.o coll_uk_res.o coll_uk_UA_res.o coll_vi_res.o coll_vi_VN_res.o \
 coll_zh_res.o coll_zh__res.o coll_zh_CN_res.o coll_zh_HK_res.o coll_zh_Hant_res.o \
 coll_zh_MO_res.o coll_zh_SG_res.o coll_zh_TW_res.o coll_zh_TW_STROKE_res.o \
 coll_zh__PINYIN_res.o cs_res.o cs_CZ_res.o cy_res.o cy_GB_res.o da_res.o \
 da_DK_res.o de_res.o de_AT_res.o de_BE_res.o de_CH_res.o de_DE_res.o \
 de_LU_res.o ebcdic_xml_us_cnv.o el_res.o el_GR_res.o en_res.o en_AU_res.o \
 en_BE_res.o en_BW_res.o en_CA_res.o en_GB_res.o en_HK_res.o en_IE_res.o \
 en_IN_res.o en_MT_res.o en_NZ_res.o en_PH_res.o en_PK_res.o en_RH_res.o \
 en_SG_res.o en_US_res.o en_US_POSIX_res.o en_VI_res.o en_ZA_res.o \
 en_ZW_res.o eo_res.o es_res.o es_AR_res.o es_BO_res.o es_CL_res.o es_CO_res.o \
 es_CR_res.o es_DO_res.o es_EC_res.o es_ES_res.o es_GT_res.o es_HN_res.o \
 es_MX_res.o es_NI_res.o es_PA_res.o es_PE_res.o es_PR_res.o es_PY_res.o \
 es_SV_res.o es_US_res.o es_UY_res.o es_VE_res.o et_res.o et_EE_res.o \
 eu_res.o eu_ES_res.o fa_res.o fa_AF_res.o fa_IR_res.o fi_res.o fi_FI_res.o \
 fo_res.o fo_FO_res.o fr_res.o fr_BE_res.o fr_CA_res.o fr_CH_res.o fr_FR_res.o \
 fr_LU_res.o ga_res.o ga_IE_res.o gb18030_cnv.o gl_res.o gl_ES_res.o \
 gu_res.o gu_IN_res.o gv_res.o gv_GB_res.o haw_res.o haw_US_res.o he_res.o \
 he_IL_res.o hi_res.o hi_IN_res.o hr_res.o hr_HR_res.o hu_res.o hu_HU_res.o \
 hy_res.o hy_AM_res.o hy_AM_REVISED_res.o ibm_1006_P100_1995_cnv.o \
 ibm_1025_P100_1995_cnv.o ibm_1026_P100_1995_cnv.o ibm_1047_P100_1995_cnv.o \
 ibm_1051_P100_1995_cnv.o ibm_1089_P100_1995_cnv.o ibm_1097_P100_1995_cnv.o \
 ibm_1098_P100_1995_cnv.o ibm_1112_P100_1995_cnv.o ibm_1122_P100_1999_cnv.o \
 ibm_1123_P100_1995_cnv.o ibm_1124_P100_1996_cnv.o ibm_1125_P100_1997_cnv.o \
 ibm_1129_P100_1997_cnv.o ibm_1130_P100_1997_cnv.o ibm_1131_P100_1997_cnv.o \
 ibm_1132_P100_1998_cnv.o ibm_1133_P100_1997_cnv.o ibm_1137_P100_1999_cnv.o \
 ibm_1140_P100_1997_cnv.o ibm_1141_P100_1997_cnv.o ibm_1142_P100_1997_cnv.o \
 ibm_1143_P100_1997_cnv.o ibm_1144_P100_1997_cnv.o ibm_1145_P100_1997_cnv.o \
 ibm_1146_P100_1997_cnv.o ibm_1147_P100_1997_cnv.o ibm_1148_P100_1997_cnv.o \
 ibm_1149_P100_1997_cnv.o ibm_1153_P100_1999_cnv.o ibm_1154_P100_1999_cnv.o \
 ibm_1155_P100_1999_cnv.o ibm_1156_P100_1999_cnv.o ibm_1157_P100_1999_cnv.o \
 ibm_1158_P100_1999_cnv.o ibm_1160_P100_1999_cnv.o ibm_1162_P100_1999_cnv.o \
 ibm_1164_P100_1999_cnv.o ibm_1168_P100_2002_cnv.o ibm_1250_P100_1995_cnv.o \
 ibm_1251_P100_1995_cnv.o ibm_1252_P100_2000_cnv.o ibm_1253_P100_1995_cnv.o \
 ibm_1254_P100_1995_cnv.o ibm_1255_P100_1995_cnv.o ibm_1256_P110_1997_cnv.o \
 ibm_1257_P100_1995_cnv.o ibm_1258_P100_1997_cnv.o ibm_12712_P100_1998_cnv.o \
 ibm_1276_P100_1995_cnv.o ibm_1363_P110_1997_cnv.o ibm_1363_P11B_1998_cnv.o \
 ibm_1364_P110_1997_cnv.o ibm_1371_P100_1999_cnv.o ibm_1373_P100_2002_cnv.o \
 ibm_1375_P100_2003_cnv.o ibm_1383_P110_1999_cnv.o ibm_1386_P100_2002_cnv.o \
 ibm_1388_P103_2001_cnv.o ibm_1390_P110_2003_cnv.o ibm_1399_P110_2003_cnv.o \
 ibm_16684_P110_2003_cnv.o ibm_16804_X110_1999_cnv.o ibm_273_P100_1995_cnv.o \
 ibm_277_P100_1995_cnv.o ibm_278_P100_1995_cnv.o ibm_280_P100_1995_cnv.o \
 ibm_284_P100_1995_cnv.o ibm_285_P100_1995_cnv.o ibm_290_P100_1995_cnv.o \
 ibm_297_P100_1995_cnv.o ibm_33722_P120_1999_cnv.o ibm_33722_P12A_1999_cnv.o \
 ibm_367_P100_1995_cnv.o ibm_37_P100_1995_cnv.o ibm_420_X120_1999_cnv.o \
 ibm_424_P100_1995_cnv.o ibm_437_P100_1995_cnv.o ibm_4517_P100_2005_cnv.o \
 ibm_4899_P100_1998_cnv.o ibm_4909_P100_1999_cnv.o ibm_4971_P100_1999_cnv.o \
 ibm_500_P100_1995_cnv.o ibm_5123_P100_1999_cnv.o ibm_5346_P100_1998_cnv.o \
 ibm_5347_P100_1998_cnv.o ibm_5348_P100_1997_cnv.o ibm_5349_P100_1998_cnv.o \
 ibm_5350_P100_1998_cnv.o ibm_5351_P100_1998_cnv.o ibm_5352_P100_1998_cnv.o \
 ibm_5353_P100_1998_cnv.o ibm_5354_P100_1998_cnv.o ibm_5478_P100_1995_cnv.o \
 ibm_737_P100_1997_cnv.o ibm_775_P100_1996_cnv.o ibm_803_P100_1999_cnv.o \
 ibm_813_P100_1995_cnv.o ibm_838_P100_1995_cnv.o ibm_8482_P100_1999_cnv.o \
 ibm_850_P100_1995_cnv.o ibm_851_P100_1995_cnv.o ibm_852_P100_1995_cnv.o \
 ibm_855_P100_1995_cnv.o ibm_856_P100_1995_cnv.o ibm_857_P100_1995_cnv.o \
 ibm_858_P100_1997_cnv.o ibm_860_P100_1995_cnv.o ibm_861_P100_1995_cnv.o \
 ibm_862_P100_1995_cnv.o ibm_863_P100_1995_cnv.o ibm_864_X110_1999_cnv.o \
 ibm_865_P100_1995_cnv.o ibm_866_P100_1995_cnv.o ibm_867_P100_1998_cnv.o \
 ibm_868_P100_1995_cnv.o ibm_869_P100_1995_cnv.o ibm_870_P100_1995_cnv.o \
 ibm_871_P100_1995_cnv.o ibm_874_P100_1995_cnv.o ibm_875_P100_1995_cnv.o \
 ibm_878_P100_1996_cnv.o ibm_897_P100_1995_cnv.o ibm_9005_X100_2005_cnv.o \
 ibm_901_P100_1999_cnv.o ibm_902_P100_1999_cnv.o ibm_9067_X100_2005_cnv.o \
 ibm_912_P100_1995_cnv.o ibm_913_P100_2000_cnv.o ibm_914_P100_1995_cnv.o \
 ibm_915_P100_1995_cnv.o ibm_916_P100_1995_cnv.o ibm_918_P100_1995_cnv.o \
 ibm_920_P100_1995_cnv.o ibm_921_P100_1995_cnv.o ibm_922_P100_1999_cnv.o \
 ibm_923_P100_1998_cnv.o ibm_930_P120_1999_cnv.o ibm_933_P110_1995_cnv.o \
 ibm_935_P110_1999_cnv.o ibm_937_P110_1999_cnv.o ibm_939_P120_1999_cnv.o \
 ibm_942_P12A_1999_cnv.o ibm_943_P130_1999_cnv.o ibm_943_P15A_2003_cnv.o \
 ibm_9447_P100_2002_cnv.o ibm_9448_X100_2005_cnv.o ibm_9449_P100_2002_cnv.o \
 ibm_949_P110_1999_cnv.o ibm_949_P11A_1999_cnv.o ibm_950_P110_1999_cnv.o \
 ibm_954_P101_2000_cnv.o ibm_964_P110_1999_cnv.o ibm_970_P110_1995_cnv.o \
 ibm_971_P100_1995_cnv.o icu_internal_25546_cnv.o id_res.o id_ID_res.o \
 in_res.o in_ID_res.o invuca_icu.o is_res.o is_IS_res.o iso_8859_10_1998_cnv.o \
 iso_8859_11_2001_cnv.o iso_8859_14_1998_cnv.o iso_ir_165_cnv.o it_res.o \
 it_CH_res.o it_IT_res.o iw_res.o iw_IL_res.o ja_res.o ja_JP_res.o ja_JP_TRADITIONAL_res.o \
 jisx_208_cnv.o jisx_212_cnv.o kk_res.o kk_KZ_res.o kl_res.o kl_GL_res.o \
 kn_res.o kn_IN_res.o ko_res.o ko_KR_res.o kok_res.o kok_IN_res.o kw_res.o \
 kw_GB_res.o lmb_excp_cnv.o lt_res.o lt_LT_res.o lv_res.o lv_LV_res.o \
 macos_0_2_10.2_cnv.o macos_2566_10.2_cnv.o macos_29_10.2_cnv.o macos_35_10.2_cnv.o \
 macos_6_2_10.4_cnv.o macos_7_3_10.2_cnv.o mk_res.o mk_MK_res.o ml_res.o \
 ml_IN_res.o mr_res.o mr_IN_res.o ms_res.o ms_BN_res.o ms_MY_res.o mt_res.o \
 mt_MT_res.o nb_res.o nb_NO_res.o nl_res.o nl_BE_res.o nl_NL_res.o nn_res.o \
 nn_NO_res.o no_res.o no_NO_res.o no_NO_NY_res.o om_res.o om_ET_res.o \
 om_KE_res.o or_res.o or_IN_res.o pa_res.o pa_IN_res.o pl_res.o pl_PL_res.o \
 pnames_icu.o ps_res.o ps_AF_res.o pt_res.o pt_BR_res.o pt_PT_res.o \
 rbnf_da_res.o rbnf_de_res.o rbnf_en_res.o rbnf_en_GB_res.o rbnf_eo_res.o \
 rbnf_es_res.o rbnf_fa_res.o rbnf_fa_AF_res.o rbnf_fr_res.o rbnf_fr_BE_res.o \
 rbnf_fr_CH_res.o rbnf_ga_res.o rbnf_he_res.o rbnf_it_res.o rbnf_ja_res.o \
 rbnf_mt_res.o rbnf_nl_res.o rbnf_pl_res.o rbnf_pt_res.o rbnf_res_index_res.o \
 rbnf_root_res.o rbnf_ru_res.o rbnf_sv_res.o rbnf_th_res.o rbnf_uk_res.o \
 res_index_res.o ro_res.o ro_RO_res.o root_res.o ru_res.o ru_RU_res.o \
 ru_UA_res.o sh_res.o sh_CS_res.o sh_YU_res.o sk_res.o sk_SK_res.o sl_res.o \
 sl_SI_res.o so_res.o so_DJ_res.o so_ET_res.o so_KE_res.o so_SO_res.o \
 sq_res.o sq_AL_res.o sr_res.o sr_CS_res.o sr_Cyrl_res.o sr_Cyrl_CS_res.o \
 sr_Cyrl_YU_res.o sr_Latn_res.o sr_Latn_CS_res.o sr_Latn_YU_res.o \
 sr_YU_res.o sv_res.o sv_FI_res.o sv_SE_res.o sw_res.o sw_KE_res.o sw_TZ_res.o \
 ta_res.o ta_IN_res.o te_res.o te_IN_res.o th_res.o th_TH_res.o th_TH_TRADITIONAL_res.o \
 ti_res.o ti_ER_res.o ti_ET_res.o tr_res.o tr_TR_res.o translit_el_res.o \
 translit_en_res.o translit_root_res.o ucadata_icu.o uidna_spp.o uk_res.o \
 uk_UA_res.o unames_icu.o ur_res.o ur_IN_res.o ur_PK_res.o uz_res.o \
 uz_Cyrl_res.o uz_Cyrl_UZ_res.o uz_Latn_res.o uz_Latn_UZ_res.o uz_UZ_res.o \
 vi_res.o vi_VN_res.o windows_874_2000_cnv.o windows_936_2000_cnv.o \
 windows_949_2000_cnv.o windows_950_2000_cnv.o zh_res.o zh_CN_res.o \
 zh_HK_res.o zh_Hans_res.o zh_Hans_CN_res.o zh_Hans_SG_res.o zh_Hant_res.o \
 zh_Hant_HK_res.o zh_Hant_MO_res.o zh_Hant_TW_res.o zh_MO_res.o zh_SG_res.o \
 zh_TW_res.o zoneinfo_res.o
endif


OBJECTS=$(BASE_OBJECTS:%=$(TEMP_DIR)/%)

$(TEMP_DIR)/%.o: $(TEMP_DIR)/%.c
	$(COMPILE.c) $(DYNAMICCPPFLAGS) $(DYNAMICCXXFLAGS) -o $@ $<

build-objs: $(SOURCES) $(OBJECTS)

$(OBJECTS): $(SOURCES)

$(TARGETDIR)/$(FINAL_SO_TARGET): $(OBJECTS) $(LISTFILES) $(DLL_DEPS)
	$(SHLIB.c) -o $@ $(OBJECTS) $(DLL_LDFLAGS)
	-ls -l $@

CLEANFILES= $(CMNLIST) $(OBJECTS) $(HPUX_JUNK_OBJ) $(TARGETDIR)/$(FINAL_SO_TARGET) $(TARGETDIR)/$(MIDDLE_SO_TARGET) $(TARGETDIR)/$(TARGET)

clean:
	-$(RMV) $(CLEANFILES) $(MAKEFILE)

install: $(TARGETDIR)/$(FINAL_SO_TARGET)
	$(INSTALL-L) $(TARGETDIR)/$(FINAL_SO_TARGET) $(INSTALLTO)/$(FINAL_SO_TARGET)
ifneq ($(IMPORT_LIB_EXT),)
	$(INSTALL-L) $(TARGETDIR)/$(basename $(FINAL_SO_TARGET))$(IMPORT_LIB_EXT) $(INSTALLTO)/$(basename( $(FINAL_SO_TARGET))$(IMPORT_LIB_EXT)
endif
ifneq ($(FINAL_SO_TARGET),$(SO_TARGET))
	cd $(INSTALLTO) && $(RM) $(SO_TARGET) && ln -s $(FINAL_SO_TARGET) $(SO_TARGET)
ifneq ($(FINAL_SO_TARGET),$(MIDDLE_SO_TARGET))
	cd $(INSTALLTO) && $(RM) $(MIDDLE_SO_TARGET) && ln -s $(FINAL_SO_TARGET) $(MIDDLE_SO_TARGET)
endif
endif


rebuild: clean all
