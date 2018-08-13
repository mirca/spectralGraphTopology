#ifndef OPERATORS_H
#define OPERATORS_H
#include <RcppEigen.h>
// [[Rcpp::depends(RcppEigen)]]

using Eigen::VectorXd;
using Eigen::MatrixXd;
using Eigen::Map;

MatrixXd _LOp(Map<VectorXd> w, int n);
VectorXd _LStarOp(Map<MatrixXd> Y);
#endif