---
layout: default
title: Grid
parent: Structured graphs
nav_order: 1
---

# Grid
{: .no_toc }

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

``` r
library(spectralGraphTopology)
library(igraph)
library(viridis)
set.seed(0)

p <- 64
grid <- make_lattice(length = sqrt(p), dim = 2)
n <- as.integer(100 * p)
E(grid)$weight <- runif(gsize(grid), min = 1e-1, max = 3)
Ltrue <- as.matrix(laplacian_matrix(grid))
Wtrue <- diag(diag(Ltrue)) - Ltrue
Y <- MASS::mvrnorm(n, mu = rep(0, p), Sigma = MASS::ginv(Ltrue))
S <- cov(Y)
graph <- learn_k_component_graph(S, w0 = "qp", beta = 20, alpha = 5e-3, abstol = 1e-5, verbose = FALSE)
graph$Adjacency[graph$Adjacency < 5e-2] <- 0
estimated_grid <- graph_from_adjacency_matrix(graph$Adjacency, mode = "undirected", weighted = TRUE)
colors <- viridis(20, begin = 0, end = 1, direction = -1)
c_scale <- colorRamp(colors)
E(estimated_grid)$color = apply(c_scale(E(estimated_grid)$weight / max(E(estimated_grid)$weight)), 1,
                          function(x) rgb(x[1]/255, x[2]/255, x[3]/255))
E(grid)$color = apply(c_scale(E(grid)$weight / max(E(grid)$weight)), 1,
                      function(x) rgb(x[1]/255, x[2]/255, x[3]/255))
V(estimated_grid)$color = "grey"
V(grid)$color = "grey"
la <- layout_on_grid(grid)
plot(grid, layout = la, vertex.label = NA, vertex.size = 3)
plot(estimated_grid, layout = la, vertex.label = NA, vertex.size = 3)
```

True grid graph            |  Learned grid graph
:-------------------------:|:-------------------------:
![](grid_files/figure-markdown_github/unnamed-chunk-1-1.png) | ![](grid_files/figure-markdown_github/unnamed-chunk-1-2.png)