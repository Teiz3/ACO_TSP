data = readtable('data_small_AS-MA.xlsx', 'Sheet', 'small MA AS');
small_problems = {'att48','berlin52','eil51','eil76','pr76','st70'};

for i = 1:length(small_problems)
    probelm = small_problems{i};
    % need to do (1:100) since in the excel there is the mean,stdev and
    % some more in the same column leading to a NaN and then a couple
    % values followed by more NaN due to another one taking 600 rows
    AS = data.([probelm '_AS_1'])(1:100);
    MA = data.([probelm '_MA_1'])(1:100);
    % AS
    figure;
    normplot(AS);
    title(['Q-Q Plot for algorithm AS on problem ' probelm]);
    grid on;
    [h, p] = adtest(AS);
    fprintf('Running %s on the algorithm AS gave: p = %.5f, h = %d\n', probelm, p, h);
    % MA
    figure;
    normplot(MA);
    title(['Q-Q Plot for algorithm MA on problem ' probelm]);
    grid on;
    [h, p] = adtest(MA);
    fprintf('Running %s on the algorithm MA gave: p = %.5f, h = %d\n', probelm, p, h);
end

% all small problems AS
aggregated_small_AS = data.all_AS;
figure;
normplot(aggregated_small_AS);
title('Q-Q Plot for AS on all small problems');
grid on;
[h, p] = adtest(aggregated_small_AS);
fprintf('All small problems on AS: p = %.5f, h = %d\n', p, h);

% all small problems MA
aggregated_small_MA = data.all_MA;
figure;
normplot(aggregated_small_MA);
title('Q-Q Plot for AS on all small problems');
grid on;
[h, p] = adtest(aggregated_small_MA);
fprintf('All small problems on MA: p = %.5f, h = %d\n', p, h);

% didnt put all in the excel files so looked up specific values needed for
% the upcoming wilcox test (mean of every algo, problem combination)
% normalized mean for all small problems on AS,MA
% order of the problems is: att48, berlin52, eil51, eil76, pr76, st70
% rounding up to 4 digits after the .
problem_sizes_small = [48, 52, 51, 76, 76, 70];
small_AS = [0.0528, 0.0172, 0.0631, 0.0631, 0.0838, 0.0822];
small_MA = [0.4822, 0.5318, 0.6673, 0.9252, 0.8557, 0.7916];
[p_small, h_small, stats_small] = signrank(small_AS, small_MA, 'tail', 'left');

% order of the problems is: a280, bier127, ch130, ch150, eil101, kroA200,
% lin105, pr124, pr136, tsp225 again 4 digits after the .
problem_sizes_medium = [280, 127, 130, 150, 101, 200, 105, 124, 136, 225];
medium_AS = [0.2756, 0.0856, 0.1300, 0.0694, 0.1454, 0.1975, 0.0345, 0.0271, 0.1723, 0.1781];
medium_MA = [2.4814, 1.0007, 1.2869, 1.5805, 1.1221, 1.7530, 0.9654, 1.1469, 1.3306, 1.979];
[p_medium, h_medium, stats_medium] = signrank(medium_AS, medium_MA, 'tail', 'left');

% order of the problems is: lin318, rat575, rd400
problem_sizes_large = [318, 575, 400];
large_AS = [0.1922, 0.3550, 0.2761];
large_MA = [2.1113, 3.3079, 2.4753];
[p_large, h_large, stats_large] = signrank(large_AS, large_MA, 'tail', 'left');

disp(['Small problems: p =  ', num2str(p_small), ', h = ', num2str(h_small)]);
disp(['Medium problems:  p = ', num2str(p_medium), ', h = ', num2str(h_medium)]);
disp(['Large problems: p = ', num2str(p_large), ', h = ', num2str(h_large)]);

% visualize the normalized means of AS and MA against prblm size
figure;
hold on;
scatter(problem_sizes_small, small_AS, 60, 'o', 'filled', 'DisplayName', 'Small AS');
scatter(problem_sizes_medium, medium_AS, 60, 'o', 'filled', 'DisplayName', 'Medium AS');
scatter(problem_sizes_large, large_AS, 80, 'o', 'filled', 'DisplayName', 'Large AS');
scatter(problem_sizes_small, small_MA, 60, 'x', 'DisplayName', 'Small MA');
scatter(problem_sizes_medium, medium_MA, 60, 'x', 'DisplayName', 'Medium MA');
scatter(problem_sizes_large, large_MA, 80, 'x', 'DisplayName', 'Large MA');
xlabel('Problem Size (number of vertices)');
ylabel('Normalized Mean Solution');
title('AS and MA normalized mean solutions against problem size');
legend('show');
grid on;
hold off;

