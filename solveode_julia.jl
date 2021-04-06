using BenchmarkTools
using DifferentialEquations

function main()
    x1 = 0.00001
    xf = 11.0
    eps = 1.0E-15
    
    y1 = [ 0.99998416139571, -1.58175227379914 ]

    u0 = [y1[1]; y1[2]]
    tspan = (x1, xf)
    prob = ODEProblem(equation!, u0, tspan)
    sol = solve(prob, abstol = eps, reltol = eps)
    y = [sol.u[size(sol.u)[1]][1], sol.u[size(sol.u)[1]][2]]

    return y
end

function equation!(du, u, p, t)
    du[1] = u[2]
    du[2] = u[1] * sqrt(u[1] / t)
end

@btime main()
