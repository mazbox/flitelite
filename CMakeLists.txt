cmake_minimum_required(VERSION 3.25)

# Set the project name
project(flitelite)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)
include_directories(include lib lib/private-includes lib/lang/usenglish lib/lang/cmulex lib/cg)


add_library(flitelite STATIC
        ./lib/lang/cmu_grapheme_lang/cmu_grapheme_lang.c
        ./lib/lang/cmu_grapheme_lang/cmu_grapheme_phoneset.c
        ./lib/lang/cmu_grapheme_lang/cmu_grapheme_phrasing_cart.c
        ./lib/lang/cmu_grapheme_lang/graph_gpos.c
        ./lib/lang/cmu_us_slt/cmu_us_slt.c
        ./lib/lang/cmu_us_slt/cmu_us_slt_spamf0_accent_params.c
        ./lib/lang/cmu_us_slt/cmu_us_slt_cg.c
        ./lib/lang/cmu_us_slt/cmu_us_slt_cg_f0_trees.c
        ./lib/lang/cmu_us_slt/cmu_us_slt_spamf0_accent.c
        ./lib/lang/cmu_us_slt/cmu_us_slt_cg_single_mcep_trees.c
        ./lib/lang/cmu_us_slt/cmu_us_slt_cg_phonestate.c
        ./lib/lang/cmu_us_slt/cmu_us_slt_cg_durmodel.c
        ./lib/lang/cmu_us_slt/cmu_us_slt_cg_single_params.c
        ./lib/lang/cmu_us_slt/cmu_us_slt_spamf0_phrase.c
        ./lib/lang/cmulex/cmu_lex_entries.c
        ./lib/lang/cmulex/cmu_lex.c
        ./lib/lang/cmulex/cmu_postlex.c
        ./lib/lang/cmulex/cmu_lts_rules.c
        ./lib/lang/cmulex/cmu_lts_model.c
        ./lib/lang/cmulex/cmu_lex_data.c
        ./lib/lang/usenglish/us_durz_cart.c
        ./lib/lang/usenglish/us_int_tone_cart.c
        ./lib/lang/usenglish/us_pos_cart.c
        ./lib/lang/usenglish/us_phoneset.c
        ./lib/lang/usenglish/us_text.c
        ./lib/lang/usenglish/us_dur_stats.c
        ./lib/lang/usenglish/us_gpos.c
        ./lib/lang/usenglish/us_f0lr.c
        ./lib/lang/usenglish/us_ffeatures.c
        ./lib/lang/usenglish/usenglish.c
        ./lib/lang/usenglish/us_phrasing_cart.c
        ./lib/lang/usenglish/us_f0_model.c
        ./lib/lang/usenglish/us_int_accent_cart.c
        ./lib/lang/usenglish/us_nums_cart.c
        ./lib/lang/usenglish/us_aswd.c
        ./lib/lang/usenglish/us_expand.c
        ./lib/lang/cmu_grapheme_lex/cmu_grapheme_lex.c
        ./lib/lang/cmu_grapheme_lex/grapheme_unitran_tables.c
        #        ./main/flite_main.cpp
        ./lib/FestivalSpeechSynth.cpp
        ./lib/flite_lang_list.c
        ./lib/flite_voice_list.c
        ./lib/flite_lite_config.h
        ./lib/hrg/cst_item.c
        ./lib/hrg/cst_rel_io.c
        ./lib/hrg/cst_ffeature.c
        ./lib/hrg/cst_utterance.c
        ./lib/hrg/cst_relation.c
        ./lib/cg/cst_cg_load_voice.c
        ./lib/cg/cst_vc.c
        ./lib/cg/cst_cg_dump_voice.c
        ./lib/cg/cst_mlsa.c
        ./lib/cg/cst_spamf0.c
        ./lib/cg/cst_mlpg.c
        ./lib/cg/cst_cg.c
        ./lib/cg/cst_cg_map.c
        ./lib/utils/cst_socket.c
        ./lib/utils/cst_string.c
        ./lib/utils/cst_val_user.c
        ./lib/utils/cst_url.c
        ./lib/utils/cst_error.c
        ./lib/utils/cst_val.c
        ./lib/utils/cst_val_const.c
        ./lib/utils/cst_wchar.c
        ./lib/utils/cst_mmap_posix.c
        ./lib/utils/cst_tokenstream.c
        ./lib/utils/cst_endian.c
        ./lib/utils/cst_args.c
        ./lib/utils/cst_alloc.c
        ./lib/utils/cst_features.c
        ./lib/utils/cst_file_stdio.c
        ./lib/regex/cst_regex.c
        ./lib/regex/regexp.c
        ./lib/regex/regsub.c
        ./lib/speech/cst_wave_io.c
        ./lib/speech/cst_lpcres.c
        ./lib/speech/cst_wave_utils.c
        ./lib/speech/g72x.c
        ./lib/speech/cst_track_io.c
        ./lib/speech/g723_40.c
        ./lib/speech/rateconv.c
        ./lib/speech/cst_wave.c
        ./lib/speech/g723_24.c
        ./lib/speech/cst_track.c
        ./lib/speech/g721.c
        ./lib/synth/cst_phoneset.c
        ./lib/synth/cst_ffeatures.c
        ./lib/synth/flite.c
        ./lib/synth/cst_synth.c
        ./lib/synth/cst_ssml.c
        ./lib/synth/cst_utt_utils.c
        ./lib/synth/cst_voice.c
        ./lib/audio/auserver.c
        ./lib/audio/au_none.c
        ./lib/audio/au_command.c
        ./lib/audio/au_streaming.c
        ./lib/audio/auclient.c
        ./lib/audio/audio.c
        ./lib/lexicon/cst_lts.c
        ./lib/lexicon/cst_lexicon.c
        ./lib/lexicon/cst_lts_rewrites.c
        ./lib/wavesynth/cst_diphone.c
        ./lib/wavesynth/cst_reflpc.c
        ./lib/wavesynth/cst_sigpr.c
        ./lib/wavesynth/cst_sts.c
        ./lib/wavesynth/cst_units.c
        ./lib/wavesynth/cst_clunits.c
        ./lib/stats/cst_viterbi.c
        ./lib/stats/cst_cart.c
        ./lib/stats/cst_ss.c

)
target_include_directories(flitelite PUBLIC include)

# add sources as source group
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Add the executable
#add_executable(Flite ${SOURCES})

