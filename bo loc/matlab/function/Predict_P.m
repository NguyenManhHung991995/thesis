function P_p=Predict_P(x_c,T,P_k_1,q)% x_p: x predicted, x_c: x_corrected
C3=[0,-x_c(3),x_c(2);x_c(3),0,-x_c(1);-x_c(2),x_c(1),0];
Ak=[eye(3,3),T*C3;zeros(3,3),eye(3,3)];
Qk=q*[T^3*C3*C3',T^2*C3;T^2*C3',T*eye(3,3)];
P_p=Ak*P_k_1*Ak'+Qk;
end