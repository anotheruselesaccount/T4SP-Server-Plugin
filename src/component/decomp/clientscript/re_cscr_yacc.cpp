#include <stdinc.hpp>
#include "loader/component_loader.hpp"
#include "utils/hook.hpp"
#include "codsrc/clientscript/cscr_yacc.hpp"

#ifndef DISABLE_RE_CSCR_YACC
namespace re_cscr_yacc
{
	utils::hook::detour LowerCase_hook;
	utils::hook::detour yyparse_hook;
	utils::hook::detour StringValue_hook;
	utils::hook::detour yylex_hook;
	utils::hook::detour yy_get_next_buffer_hook;
	utils::hook::detour yy_get_previous_state_hook;
	utils::hook::detour yy_try_NUL_trans_hook;
	utils::hook::detour yyrestart_hook;
	utils::hook::detour yy_create_buffer_hook;
	utils::hook::detour yy_flush_buffer_hook;
	utils::hook::detour ScriptParse_hook;

	namespace
	{

		unsigned int LowerCase_call(unsigned int strVal, [[maybe_unused]] void* caller_addr)
		{
#ifdef RE_CSCR_YACC_USE_WRAPPERS
			return game::LowerCase(strVal, LowerCase_hook.get_original());
#else
			return codsrc::LowerCase(strVal);
#endif
		}

		// unsigned int __usercall LowerCase@<eax>(unsigned int strVal@<ecx>)
		NAKED unsigned int LowerCase_stub()
		{
			_asm
			{
				push ecx;
				call LowerCase_call;
				add esp, 0x4;
				ret;
			}
		}

		int yyparse_stub()
		{
#ifdef RE_CSCR_YACC_USE_WRAPPERS
			return yyparse_hook.invoke<int>();
#else
			return codsrc::yyparse();
#endif
		}

		int StringValue_call(int len, const char * str_, [[maybe_unused]] void* caller_addr)
		{
#ifdef RE_CSCR_YACC_USE_WRAPPERS
			return game::StringValue(len, str_, StringValue_hook.get_original());
#else
			return codsrc::StringValue(len, str_);
#endif
		}

		// int __usercall StringValue@<eax>(int len@<ecx>, const char *str@<edx>)
		NAKED int StringValue_stub()
		{
			_asm
			{
				push edx;
				push ecx;
				call StringValue_call;
				add esp, 0x8;
				ret;
			}
		}

		int yylex_stub()
		{
#ifdef RE_CSCR_YACC_USE_WRAPPERS
			return yylex_hook.invoke<int>();
#else
			return codsrc::yylex();
#endif
		}

		int yy_get_next_buffer_stub()
		{
#ifdef RE_CSCR_YACC_USE_WRAPPERS
			return yy_get_next_buffer_hook.invoke<int>();
#else
			return codsrc::yy_get_next_buffer();
#endif
		}

		int yy_get_previous_state_stub()
		{
#ifdef RE_CSCR_YACC_USE_WRAPPERS
			return yy_get_previous_state_hook.invoke<int>();
#else
			return codsrc::yy_get_previous_state();
#endif
		}

		int yy_try_NUL_trans_call(int yy_current_state, [[maybe_unused]] void* caller_addr)
		{
#ifdef RE_CSCR_YACC_USE_WRAPPERS
			return game::yy_try_NUL_trans(yy_current_state, yy_try_NUL_trans_hook.get_original());
#else
			return codsrc::yy_try_NUL_trans(yy_current_state);
#endif
		}

		// int __usercall yy_try_NUL_trans@<eax>(int yy_current_state@<eax>)
		NAKED int yy_try_NUL_trans_stub()
		{
			_asm
			{
				push eax;
				call yy_try_NUL_trans_call;
				add esp, 0x4;
				ret;
			}
		}

		void yyrestart_stub()
		{
#ifdef RE_CSCR_YACC_USE_WRAPPERS
			yyrestart_hook.invoke<void>();
#else
			codsrc::yyrestart();
#endif
		}

		game::yy_buffer_state * yy_create_buffer_stub()
		{
#ifdef RE_CSCR_YACC_USE_WRAPPERS
			return yy_create_buffer_hook.invoke<game::yy_buffer_state *>();
#else
			return codsrc::yy_create_buffer();
#endif
		}

		void yy_flush_buffer_call(game::yy_buffer_state * result, [[maybe_unused]] void* caller_addr)
		{
#ifdef RE_CSCR_YACC_USE_WRAPPERS
			game::yy_flush_buffer(result, yy_flush_buffer_hook.get_original());
#else
			codsrc::yy_flush_buffer(result);
#endif
		}

		// void __usercall yy_flush_buffer(game::yy_buffer_state *result@<eax>)
		NAKED void yy_flush_buffer_stub()
		{
			_asm
			{
				push eax;
				call yy_flush_buffer_call;
				add esp, 0x4;
				ret;
			}
		}

		void ScriptParse_call(game::scriptInstance_t a1, [[maybe_unused]] void* caller_addr, game::sval_u * parseData)
		{
#ifdef RE_CSCR_YACC_USE_WRAPPERS
			game::ScriptParse(a1, parseData, ScriptParse_hook.get_original());
#else
			codsrc::ScriptParse(a1, parseData);
#endif
		}

		// void __usercall ScriptParse(game::scriptInstance_t a1@<eax>, game::sval_u *parseData)
		NAKED void ScriptParse_stub()
		{
			_asm
			{
				push eax;
				call ScriptParse_call;
				add esp, 0x4;
				ret;
			}
		}
	}

	class component final : public component_interface
	{
	public:
		void post_unpack() override
		{
			bool quick = true;
#ifdef RE_CSCR_YACC_USE_WRAPPERS
			quick = false;
#endif

			LowerCase_hook.create(game::LowerCase(), LowerCase_stub, quick);
			yyparse_hook.create(game::yyparse.get(), yyparse_stub, quick);
			StringValue_hook.create(game::StringValue(), StringValue_stub, quick);
			yylex_hook.create(game::yylex.get(), yylex_stub, quick);
			yy_get_next_buffer_hook.create(game::yy_get_next_buffer.get(), yy_get_next_buffer_stub, quick);
			yy_get_previous_state_hook.create(game::yy_get_previous_state.get(), yy_get_previous_state_stub, quick);
			yy_try_NUL_trans_hook.create(game::yy_try_NUL_trans(), yy_try_NUL_trans_stub, quick);
			yyrestart_hook.create(game::yyrestart.get(), yyrestart_stub, quick);
			yy_create_buffer_hook.create(game::yy_create_buffer.get(), yy_create_buffer_stub, quick);
			yy_flush_buffer_hook.create(game::yy_flush_buffer(), yy_flush_buffer_stub, quick);
			ScriptParse_hook.create(game::ScriptParse(), ScriptParse_stub, quick);
		}

	private:
	};
}
REGISTER_COMPONENT(re_cscr_yacc::component)
#endif
