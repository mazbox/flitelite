cmake_minimum_required(VERSION 3.25)

# Set the project name
project(Flite)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(include lang/usenglish lang/cmulex)


set(SOURCES
./lang/cmu_grapheme_lang/cmu_grapheme_lang.c
./lang/cmu_grapheme_lang/cmu_grapheme_phoneset.c
./lang/cmu_grapheme_lang/cmu_grapheme_phrasing_cart.c
./lang/cmu_grapheme_lang/graph_gpos.c
./lang/cmu_us_slt/cmu_us_slt.c
./lang/cmu_us_slt/cmu_us_slt_spamf0_accent_params.c
./lang/cmu_us_slt/cmu_us_slt_cg.c
./lang/cmu_us_slt/cmu_us_slt_cg_f0_trees.c
./lang/cmu_us_slt/cmu_us_slt_spamf0_accent.c
./lang/cmu_us_slt/cmu_us_slt_cg_single_mcep_trees.c
./lang/cmu_us_slt/cmu_us_slt_cg_phonestate.c
./lang/cmu_us_slt/cmu_us_slt_cg_durmodel.c
./lang/cmu_us_slt/cmu_us_slt_cg_single_params.c
./lang/cmu_us_slt/cmu_us_slt_spamf0_phrase.c
./lang/cmulex/cmu_lex_entries.c
./lang/cmulex/cmu_lex.c
./lang/cmulex/cmu_postlex.c
./lang/cmulex/cmu_lts_rules.c
./lang/cmulex/cmu_lts_model.c
./lang/cmulex/cmu_lex_data.c
./lang/usenglish/us_durz_cart.c
./lang/usenglish/us_int_tone_cart.c
./lang/usenglish/us_pos_cart.c
./lang/usenglish/us_phoneset.c
./lang/usenglish/us_text.c
./lang/usenglish/us_dur_stats.c
./lang/usenglish/us_gpos.c
./lang/usenglish/us_f0lr.c
./lang/usenglish/us_ffeatures.c
./lang/usenglish/usenglish.c
./lang/usenglish/us_phrasing_cart.c
./lang/usenglish/us_f0_model.c
./lang/usenglish/us_int_accent_cart.c
./lang/usenglish/us_nums_cart.c
./lang/usenglish/us_aswd.c
./lang/usenglish/us_expand.c
./lang/cmu_grapheme_lex/cmu_grapheme_lex.c
./lang/cmu_grapheme_lex/grapheme_unitran_tables.c
./main/flite_main.c
./main/flite_lang_list.c
./main/flite_voice_list.c
./src/hrg/cst_item.c
./src/hrg/cst_rel_io.c
./src/hrg/cst_ffeature.c
./src/hrg/cst_utterance.c
./src/hrg/cst_relation.c
./src/cg/cst_cg_load_voice.c
./src/cg/cst_vc.c
./src/cg/cst_cg_dump_voice.c
./src/cg/cst_mlsa.c
./src/cg/cst_spamf0.c
./src/cg/cst_mlpg.c
./src/cg/cst_cg.c
./src/cg/cst_cg_map.c
./src/utils/cst_socket.c
./src/utils/cst_string.c
./src/utils/cst_val_user.c
./src/utils/cst_url.c
./src/utils/cst_error.c
./src/utils/cst_val.c
./src/utils/cst_val_const.c
./src/utils/cst_wchar.c
./src/utils/cst_mmap_posix.c
./src/utils/cst_tokenstream.c
./src/utils/cst_endian.c
./src/utils/cst_args.c
./src/utils/cst_alloc.c
./src/utils/cst_features.c
./src/utils/cst_file_stdio.c
./src/regex/cst_regex.c
./src/regex/regexp.c
./src/regex/regsub.c
./src/speech/cst_wave_io.c
./src/speech/cst_lpcres.c
./src/speech/cst_wave_utils.c
./src/speech/g72x.c
./src/speech/cst_track_io.c
./src/speech/g723_40.c
./src/speech/rateconv.c
./src/speech/cst_wave.c
./src/speech/g723_24.c
./src/speech/cst_track.c
./src/speech/g721.c
./src/synth/cst_phoneset.c
./src/synth/cst_ffeatures.c
./src/synth/flite.c
./src/synth/cst_synth.c
./src/synth/cst_ssml.c
./src/synth/cst_utt_utils.c
./src/synth/cst_voice.c
./src/audio/auserver.c
./src/audio/au_none.c
./src/audio/au_command.c
./src/audio/au_streaming.c
./src/audio/auclient.c
./src/audio/audio.c
./src/lexicon/cst_lts.c
./src/lexicon/cst_lexicon.c
./src/lexicon/cst_lts_rewrites.c
./src/wavesynth/cst_diphone.c
./src/wavesynth/cst_reflpc.c
./src/wavesynth/cst_sigpr.c
./src/wavesynth/cst_sts.c
./src/wavesynth/cst_units.c
./src/wavesynth/cst_clunits.c
./src/stats/cst_viterbi.c
./src/stats/cst_cart.c
./src/stats/cst_ss.c

)

# add sources as source group
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Add the executable
add_executable(Flite ${SOURCES})

