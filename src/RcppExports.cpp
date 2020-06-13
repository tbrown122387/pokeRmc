// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// preFlopComp
CharacterVector preFlopComp(CharacterVector your_cards, IntegerVector num_sims, IntegerVector num_folders, IntegerVector num_oppo);
RcppExport SEXP _pokeRmc_preFlopComp(SEXP your_cardsSEXP, SEXP num_simsSEXP, SEXP num_foldersSEXP, SEXP num_oppoSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type your_cards(your_cardsSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type num_sims(num_simsSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type num_folders(num_foldersSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type num_oppo(num_oppoSEXP);
    rcpp_result_gen = Rcpp::wrap(preFlopComp(your_cards, num_sims, num_folders, num_oppo));
    return rcpp_result_gen;
END_RCPP
}
// preTurnComp
CharacterVector preTurnComp(CharacterVector your_cards, IntegerVector num_sims, IntegerVector num_folders, IntegerVector num_oppo, CharacterVector comm_cards);
RcppExport SEXP _pokeRmc_preTurnComp(SEXP your_cardsSEXP, SEXP num_simsSEXP, SEXP num_foldersSEXP, SEXP num_oppoSEXP, SEXP comm_cardsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type your_cards(your_cardsSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type num_sims(num_simsSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type num_folders(num_foldersSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type num_oppo(num_oppoSEXP);
    Rcpp::traits::input_parameter< CharacterVector >::type comm_cards(comm_cardsSEXP);
    rcpp_result_gen = Rcpp::wrap(preTurnComp(your_cards, num_sims, num_folders, num_oppo, comm_cards));
    return rcpp_result_gen;
END_RCPP
}
// preRiverComp
CharacterVector preRiverComp(CharacterVector your_cards, IntegerVector num_sims, IntegerVector num_folders, IntegerVector num_oppo, CharacterVector comm_cards);
RcppExport SEXP _pokeRmc_preRiverComp(SEXP your_cardsSEXP, SEXP num_simsSEXP, SEXP num_foldersSEXP, SEXP num_oppoSEXP, SEXP comm_cardsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type your_cards(your_cardsSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type num_sims(num_simsSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type num_folders(num_foldersSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type num_oppo(num_oppoSEXP);
    Rcpp::traits::input_parameter< CharacterVector >::type comm_cards(comm_cardsSEXP);
    rcpp_result_gen = Rcpp::wrap(preRiverComp(your_cards, num_sims, num_folders, num_oppo, comm_cards));
    return rcpp_result_gen;
END_RCPP
}
// postRiverComp
CharacterVector postRiverComp(CharacterVector your_cards, IntegerVector num_sims, IntegerVector num_folders, IntegerVector num_oppo, CharacterVector comm_cards);
RcppExport SEXP _pokeRmc_postRiverComp(SEXP your_cardsSEXP, SEXP num_simsSEXP, SEXP num_foldersSEXP, SEXP num_oppoSEXP, SEXP comm_cardsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type your_cards(your_cardsSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type num_sims(num_simsSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type num_folders(num_foldersSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type num_oppo(num_oppoSEXP);
    Rcpp::traits::input_parameter< CharacterVector >::type comm_cards(comm_cardsSEXP);
    rcpp_result_gen = Rcpp::wrap(postRiverComp(your_cards, num_sims, num_folders, num_oppo, comm_cards));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_pokeRmc_preFlopComp", (DL_FUNC) &_pokeRmc_preFlopComp, 4},
    {"_pokeRmc_preTurnComp", (DL_FUNC) &_pokeRmc_preTurnComp, 5},
    {"_pokeRmc_preRiverComp", (DL_FUNC) &_pokeRmc_preRiverComp, 5},
    {"_pokeRmc_postRiverComp", (DL_FUNC) &_pokeRmc_postRiverComp, 5},
    {NULL, NULL, 0}
};

RcppExport void R_init_pokeRmc(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
