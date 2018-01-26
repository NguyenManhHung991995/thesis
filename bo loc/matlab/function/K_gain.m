function K_k=K_gain(P_p,H_k,R_k)
K_k=P_p*H_k'*(H_k*P_p*H_k'+R_k);
end